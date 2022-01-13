### DESCRIPTION TEST

**Présentation:**

Le script bash *configure* compile les exécutables (dans leurs dossier respectifs) et crée un lien symbolique pour chaque executables.

Le test *autorun* est un script perl, qui si les lien symbolique des executable n'existe pas, appel le script configure, puis pour chaques fichier dans le dossier test, va le faire executer sur la **phase2** (linker) puis executer sa sortie avec la **phase1** (read-elf -a ...).

**Resultat attendu:**

Le fichier 10M.o devrait renvoyer une erreur car ce n'est pas un fichier ELF. Ce test sert a vérifier si le programme reconnais bien les fichiers ELF seulement. 
Les autres fichiers servent a vérifié si tous se déroule sans erreur.
