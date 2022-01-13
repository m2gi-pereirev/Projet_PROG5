Toutes les fichiers display servent a afficher les differentes resultats suivants l'option choisis de façon identique que la commande readelf.

### **utils:h**

Dans le fichier utils.h, nous créeons des structures pour nous aidez dans la recuperation des données dans le fichier ELF necessaire différente situation.

### Section_header_read:
-
Sert a stocker des informations pour l'affichage de la section. On y retrouve le nombre de sections, les differents noms des sections stocker dans un tableau et le contenue d'une section.

### Symbols_table_namend:
-
Sert a stocker des informations pour l'affichage de la table des symbole. On y retrouve le nombre de symbole dans la table, le symbole stocker dans un tableau et toute les information que nous donne sa structure.

### Rel_section_named:
-
Sert a stocker des informations pour l'affichage de la table de réalocation. On y retrouve un bool qui nous sert a savoir si cette table est de type addend ou non, le nombre d'element a reallouer, leur nom, la valeur, l'adresse ou il doit etre réalouer et l'adresse ou il doit etre realouer additionné a l'ajout si il y en a un.


### **read_ELF.c:**

Le fichier read_ELF.c contient toute les fonctions pour lire le fichier ELF, récupérer les données necessaires a l'affichage en fonction des options entrée en parametre et le script utilisant les differentes fonctions des fichiers display pour afficher suivant les options choisis.

### option_read:
-
**Entree**: int (nombre d'argument),char * (tableau d'argument), option d'execution, hexdump<br>
**Sortie**: tableau de char (nom des differents fichier)<br>
*Description*: Verifie si le(s) option(s) entrée(ent) en e paramètre sont valides et modifie  les differents booléen dans exec_op pour appliqué les fonctions en fonction des arguments entrés.
Verifie aussi que les fichiers données en arguments existe et les places dans un tableau qui sera renvoyé.


### init_execution:
-
**Entree**: int (nombre d'argument), tableau de char (argument), option d'execution, hexdump <br>
**Sortie**: tableau de char (nom des differents fichier)<br>
*Description*:  Initialise tous les booléen de exec_op a false puis la modifie en utilisant options_read. Il recupère aussi les differents nom de fichier grace a cette meme fonction puis les renvoies.


### is_ELF_file:
-
**Entree**: unsigned char<br>
**Sortie**: bool<br>
*Description*:  regarde si le nombre magique, qui permet d'identifier un fichier ELF, est présent et renvoie true si c'est le cas.


### is_ELF32:
-
**Entree**: unsigned char<br>
**Sortie**: bool<br>
*Description*:  Regarde si le fichier est bien un 32 bit et renvoie true si c'est le cas.


### section_index_finder:
-
**Entree**: hexdump, shdr_named<br>
**Sortie**: int<br>
*Description*:  Cherche le nom de la section rechercher dans l'entete de section.


### relocation_name_value_association:
-
**Entree**: Elf32_Rel_named, Elf32_Sym_named<br>
**Sortie**: VOID<br>
*Description*:  recupere le nom et la valeur dans la table des symboles et les associes dans la table de réalocations


### header_read:
-
**Entree**: Elf32_Ehdr, FILE<br>
**Sortie**: VOID<br>
*Description*:  Recupère l'entete du fichier ELF a l'aide de la fonction fread.


### section_headers_read:
-
**Entree**: Exec_options, FILE, Elf32_Ehdr, Elf32_Shdr_named <br>
**Sortie**: VOID<br>
*Description*:  Alloue de la mémoire sur mesure pour la structure Elf32_Shdr_named pour pouvoir ensuite se deplacé sur le fichier a l'adresse du nom de section a l'aide de fseek puis la stocker avec fread. Si la verifications de l'endianess revele que le fichier est en big endian, nous le transformons en little endian avec la fonction sections_headers_endianess. Nous allouons de la mémoire pour pouvoir stocker toute les sections. Nous nous déplassons a l'aide de fseek sur toute les adresses des sections que l'on recupère a l'aide de fread. Nous associons ensuite la section avec son nom.


### symbole_table_elf:
-
**Entree**: Exec_optionsExec_options, FILE, Elf32_Shdr_named, Elf32_Sym_named<br>
**Sortie**: VOID<br>
*Description*:  Recherche de l'adresse de la table des symboles a l'aide de la table des section. Alloue de la mémoire sur mesure pour la structure Elf32_Symb_named pour pouvoir ensuite se deplacé sur le
fichier a l'adresse du nom de symbole a l'aide de fseek puis la stocker avec fread. Si la verifications de l'endianess revele que le fichier est en big endian, nous le transformons en little endian avec 
la fonction symbole_endianess. Nous allouons de la mémoire pour pouvoir stocker toute les symboles. Nous nous déplassons a l'aide de fseek sur toute les adresses des informations sur les symbole que 
l'on recupère a l'aide de fread. Nous associons ensuite les informatins de chaque symbole avec son nom.


### section_content_read:
-
**Entree**: Exec_options, FILE, hexdump_option, Elf32_Shdr_named, char <br>
**Sortie**: int <br>
*Description*: On charge la section chercher a l'aide de section_indec_finder. On regarde ensuite si la section est vide ou non. Si elle ne l'est pas, on alloue de la mémoire pour cette section, on se
déplace a l'aide de fseek a l'adresse mémoire ou est contenue la section. Puis, on la recupère a l'aide de fread. Sinon on affiche un message disant que la section n'a pas de donnée. Les fonctions 
retourne le numéro de la section.


### relocation_sections_read:
Entree:Exec_options, FILE, Elf32_Shdr, Elf32_Rel_named<br>
**Sortie**: VOID<br>
*Description*: Utilisation d'un booléeen pour determiner quelle est le type de la réalocation. Suivant le type, calcul du nombres d'elements dans la table. Allocation de la mémoire suivant le nombre
d'élément. Deplacement a l'aide de fseek a l'adresse du debut de la table. A l'aide d'une boucle du nombre d'elements dans la table, recuperation des données a l'aide de la fonction fread. De plus, 
vérification de l'endianness.

### free_shdr_named:
-
**Entree**: Elf32_Shdr_named<br>
**Sortie**: VOID<br>
*Description*:  Libère les données de la structure Elf32_Shfr_named grace a la fonction free.


### free_sym_named:
-
**Entree**: Elf32_Sym_named <br>
**Sortie**: VOID<br>
*Description*:  Libère les données de la structure Elf32_Sym_named grace a la fonction free.


### free_rel_named:
-
**Entree**: Elf32_Rel_named<br>
**Sortie**: VOID<br>
*Description*:  Libère les données de la structure Elf32_Rel_named grace a la fonction free.


### run:
-
**Entree**: Exec_options *exec_op, char *files[], hexdump_option *hexdump<br>
**Sortie**: VOID<br>
*Description*: 


### main:
-
**Entree**: int (nombre d'argument),char * (tableau d'argument)<br>
**Sortie**: VOID<br>
*Description*: .

### load_file_content:
-
**Entree**: char \*filename<br>
**Sortie**: char \*<br>
*Description*: 

### storage_elf_content:
-
**Entree**: char \*, Elf32_file <br>
**Sortie**: VOID <br>
*Description*: 

### relocations_execution:
-
**Entree**: Elf32_file <br>
**Sortie**: VOID <br>
*Description*: 

### elf_reorganization:
-
**Entree**: Elf32_file <br>
**Sortie**: VOID <br>
*Description*: 

### load_elf_output:
-
**Entree**: char \*filename <br>
**Sortie**: FILE <br>
*Description*: 

### write_elf_content:
-
**Entree**: Elf32_file, FILE <br>
**Sortie**: VOID <br>
*Description*: 

### free_elf32_file:
-
**Entree**: Elf32_file <br>
**Sortie**: VOID <br>
*Description*: 



