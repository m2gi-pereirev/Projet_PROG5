#include "section_manipulator.h"

Elf32_stct_item *section_container_summoner(int size, char *name, char *content, bool symtab, bool rel, bool strtab,  uint32_t offset, uint32_t align, int idx)
{
	Elf32_stct_item *container = calloc(1, sizeof(Elf32_stct_item));

	//$ Allocation
	container->name = calloc(strlen(name) + 1, sizeof(char));
	container->content = calloc(size, sizeof(char));

	//$ Assignment
	container->idx = idx;
	container->symtab = symtab;
	container->rel = rel;
	container->strtab = strtab;
	container->size = size;
	container->offset = offset;
	container->align = align;
	container->next = NULL;
	strcpy(container->name, name);
	memcpy(container->content, content, size);

	return container;
}

void section_container_destroyer(Elf32_stct_item *container)
{
	free(container->name);
	free(container->content);
	free(container);
}

void sections_list_destroyer(Elf32_stct_item *cargo)
{
	if (cargo != NULL)
	{
		sections_list_destroyer(cargo->next);
		section_container_destroyer(cargo);
	}
}

void section_containers_display(Elf32_stct_item *cargo)
{
	if (cargo != NULL)
	{
		if (cargo->name != NULL)
			fprintf(stderr, "%s: 0x%hx, %d\n", cargo->name, cargo->offset, cargo->idx);
		else
			fprintf(stderr, "(null)\n");
		section_containers_display(cargo->next);
	}
}

Elf32_stct_list section_container_adder(Elf32_stct_item *cargo, char *content, char *name, int size, bool symtab, bool rel, bool strtab, Elf32_Off offset, uint32_t align, int idx)
{
	if (cargo == NULL)
	{
		Elf32_stct_item *new_container = section_container_summoner(size, name, content, symtab, rel, strtab, offset, align, idx);
		return new_container;
	}
	else
	{
		if (offset >= cargo->offset)
		{
			cargo->next = section_container_adder(cargo->next, content, name, size, symtab, rel, strtab, offset, align, idx);
			return cargo;
		}
		else
		{
			Elf32_stct_item *new_container = section_container_summoner(size, name, content, symtab, rel, strtab, offset, align, idx);
			new_container->next = cargo;
			return new_container;
		}
	}
}

bool container_exist(Elf32_stct_list cargo, uint32_t offset)
{
	if (cargo == NULL)
		return false;
	if (cargo->offset == offset)
		return true;
	return container_exist(cargo->next, offset);
}

Elf32_stct_item *finder_prev(Elf32_stct_list cargo, Elf32_stct_item *prev, uint32_t offset)
{
	if (cargo == NULL)
		return NULL;
	if (cargo->offset == offset)
		return prev;
	return finder_prev(cargo->next, cargo, offset);
}

Elf32_stct_item *finder(Elf32_stct_list cargo, uint32_t offset)
{
	if (cargo == NULL)
		return NULL;
	if (cargo->offset == offset)
		return cargo;
	return finder(cargo->next, offset);
}

Elf32_stct_item *finder_realoc(Elf32_stct_list cargo, int idx)
{
	if (cargo == NULL)
		return NULL;
	if (cargo->idx == idx)
	{
		return cargo;
	}
	return finder_realoc(cargo->next, idx);
}

Elf32_stct_item *symtab_finder(Elf32_stct_list cargo)
{
	if (cargo == NULL)
		return NULL;
	if (cargo->symtab)
		return cargo;
	return symtab_finder(cargo->next);
}

Elf32_stct_list swap_section(Elf32_stct_item *cargo, uint32_t off1, uint32_t off2)
{
	if (!container_exist(cargo, off1) && !container_exist(cargo, off2))
		return cargo;

	if (off1 == off2)
		return cargo;

	Elf32_stct_item *container1 = NULL, *container2 = NULL, *prev1 = NULL, *prev2 = NULL, *temp = NULL;

	container1 = finder(cargo, off1);
	prev1 = finder_prev(cargo, NULL, off1);
	container2 = finder(cargo, off2);
	prev2 = finder_prev(cargo, NULL, off2);

	if (container1 != NULL && container2 != NULL)
	{
		if (prev1 != NULL)
			prev1->next = container2;

		if (prev2 != NULL)
			prev2->next = container1;

		temp = container1->next;
		container1->next = container2->next;
		container2->next = temp;

		if (prev1 == NULL)
			cargo = container2;
		else if (prev2 == NULL)
			cargo = container1;
	}
	return cargo;
}

Elf32_stct_list remove_section(Elf32_stct_list cargo, uint32_t offset)
{
	Elf32_stct_item *container = NULL, *prev = NULL;

	container = finder(cargo, offset);
	prev = finder_prev(cargo, NULL, offset);

	if (container != NULL)
	{
		if (prev != NULL)
			prev->next = container->next;
		else
			cargo = container->next;

		section_container_destroyer(container);
	}
	return cargo;
}

Elf32_stct_list __section_offset_remappage(Elf32_stct_list cargo)
{
	Elf32_stct_item *prev = NULL;
	if (cargo != NULL)
	{
		finder_prev(cargo, prev, cargo->offset);
		if (prev != NULL)
		{
			cargo->offset = prev->offset + prev->size;
			return __section_offset_remappage(cargo->next);
		}
	}
	return cargo;
}

Elf32_stct_list section_offset_remappage(Elf32_stct_list cargo, uint16_t header_size)
{
	if (cargo == NULL)
		return NULL;

	Elf32_stct_item *temp = cargo->next, *prev = cargo;
	while (temp != NULL)
	{
		if (temp->align > 1)
		{
			int byte_index = prev->offset + prev->size;
			while(byte_index % temp->align != 0)
				++byte_index;
			temp->offset = byte_index;
		}
		else
			temp->offset = prev->offset + prev->size;

		prev = temp;
		temp = temp->next;
	}
	return cargo;
}

Elf32_stct_list reindex(Elf32_stct_list cargo)
{
	int idx = 1;
	Elf32_stct_list tmp = cargo;
	while (tmp != NULL)
	{
		tmp->idx = idx++;
		tmp = tmp->next;
	}
	return cargo;
}

Elf32_stct_item *last_finder(Elf32_stct_list cargo)
{
	if (cargo == NULL)
		return NULL;
	if (cargo->next != NULL)
		return last_finder(cargo->next);
	return cargo;
}
