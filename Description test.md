### DESCRIPTION TEST

**Présentation:**

Le test autorun est un srcipt bash qui compile le programme, affiche quelle fichier va etre utilisé, puis applique phase2(linker) sur le fichier et affiche le resultat a l'aide de phase1 -a (read-elf).
Tous les fichiers contenu dans le dossier test seront tester.

**Resultat attendu:**

Le fichier 10M.o devrait renvoyer une erreur car ce n'est pas un fichier ELF. Ce test sert a vérifier si le programme reconnais bien les fichiers ELF seulement. 
Les autres fichiers servent a vérifié si tous se déroule sans erreur.
