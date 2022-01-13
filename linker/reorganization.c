#include "reorganization.h"

void symbol_value_affectation(Elf32_Shdr_named *shdrn, Elf32_Sym_named *symn, Elf32_Rel_named *reln, int nb_rel)
{
	for (int i = 0; i < symn->sym_num; i++)
	{
		if (ELF32_ST_TYPE(symn->sym[i].st_info) == STT_SECTION)
			symn->sym[i].st_value = shdrn->shdr[symn->sym[i].st_shndx].sh_offset;
	}
	for (int i = 0; i < nb_rel; i++)
	{
		if(&reln[i].rel_num != NULL)
		{
			for (int j = 0; j < reln[nb_rel].rel_num; j++)
			{
				if (ELF32_ST_TYPE(symn->sym[i].st_info) == STT_SECTION)
					reln[i].sym_val[j] = symn->sym[ELF32_R_SYM(reln[i].rel[j].r_info)].st_value;
			}
		}
	}
}

Elf32_stct_list remove_rel_section(Elf32_stct_list sections_array, Elf32_Shdr_named *shdrn)
{
	for (int i = 0; i < shdrn->shnum; i++)
	{
		if (shdrn->shdr[i].sh_type == SHT_REL)
			remove_section(sections_array, shdrn->shdr[i].sh_offset);
	}
	return sections_array;
}

uint16_t new_shstrndx(Elf32_Shdr_named *shdrn)
{
	uint16_t idx = 0;
	bool is_null_writed = false;
	for (int i = 0; i < shdrn->shnum; i++)
	{
		if (!is_null_writed && shdrn->shdr[i].sh_type == SHT_NULL)
		{
			++idx;
			is_null_writed = true;
		}
		else if (shdrn->shdr[i].sh_type != SHT_NULL)
			++idx;
	}
	return idx;
}

void section_header_adresse_correction(Elf32_stct_list cargo, Elf32_Shdr_named *shdrn, Elf32_Ehdr *ehdr, Elf32_Sym_named *symn)
{
	int i = 1;
	while (cargo != NULL && i < ehdr->e_shnum)
	{
		shdrn->shdr[i].sh_offset = cargo->offset;
		shdrn->shdr[i].sh_size = cargo->size;

		if (shdrn->shdr[i].sh_type == SHT_SYMTAB)
		{
			shdrn->shdr[i].sh_info = i;
			shdrn->shdr[i].sh_link = i + 1;
		}
		++i;
		cargo = cargo->next;
	}
}

void symbols_reindex(Elf32_Sym_named *symn, Elf32_Shdr_named *shdrn)
{
	int idx;
	for (int i = 0; i < symn->sym_num; i++)
	{
		if(ELF32_ST_TYPE(symn->sym[i].st_info) == STT_SECTION)
		{
			idx = 0;
			while (symn->sym[i].st_value != shdrn->shdr[idx].sh_offset)
				++idx;
			symn->sym[i].st_shndx = idx;
		}
	}
}

void shdr_rel_entry_delete(Elf32_Shdr_named *shdrn)
{
	for (int i = 0; i < shdrn->shnum; i++)
	{
		if (shdrn->shdr[i].sh_type == SHT_REL)
		{
			for (int j = i + 1; j < shdrn->shnum; j++)
			{
				shdrn->shdr[j - 1] = shdrn->shdr[j];
			}
		}
	}
}

void elf_reorganization(Elf32_file *elf)
{
	symbol_value_affectation(elf->shdrn, elf->symn, elf->reln, elf->nb_rel);
	remove_rel_section(elf->sections_array, elf->shdrn);
	shdr_rel_entry_delete(elf->shdrn);
	elf->sections_array = reindex(elf->sections_array);
	elf->sections_array = section_offset_remappage(elf->sections_array, elf->ehdr->e_ehsize);
	Elf32_stct_item *last = last_finder(elf->sections_array);
	uint16_t nb_sh = elf->shdrn->shnum - elf->nb_rel;
	elf->ehdr->e_shnum = nb_sh;
	elf->ehdr->e_shstrndx = last->idx;
	elf->ehdr->e_shoff = last->offset + last->size;
	section_header_adresse_correction(elf->sections_array, elf->shdrn, elf->ehdr, elf->symn);
	symbols_reindex(elf->symn, elf->shdrn);
}