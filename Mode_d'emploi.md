### Mode d'emploi:

**Compilation:**

Executer le script bash pour compiler l'executable phase1 (read-elf) et phase2 (linker) a l'aide de la commande suivante:

./configure

**Execution:**

Pour executer read-elf, utiliser la commande suivante:

./read-elf -? < fichiers >

Remplacer le ? par un de ces symboles suivant l'option rechercher:

  -a --all              			Equivalent à: -H -S -r<br>
  -H --file-header      			Affiche l'entete du fichier ELF<br>
  -S --section-headers  			Affiche l'entete de sefction<br>
     --sections         			Un alias pour --section-headers<br>
  -s --syms             			Affiche la table des symboles<br>
     --symbols          			Un alias pour --syms<br>
  -r --relocs           			Affiche la table de réalocation (si présente)<br>
  -x --hex-dump=<number|name>       Vidanger le contenu de la section <numéro | nom> en octets+<br>
  -h --help            				Affiche les informations<br>
  
  Il est possible d'executer plusieurs le programmes sur plusieurs fichiers a la suite

  Pour executer linker, utiliser la commande suivante:

  ./linker < fichier1 > < fichier2 >

  Le fichier1 est le fichier ELF d'entrée et fichier2 le fichier ELF modifié de sortie. Si aucun fichier de sortie n'est données, le fichier de sortie devient out.o. 
