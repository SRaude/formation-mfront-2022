# Formation MFront (EDF-ERMES/MMC) 2022
### Objectifs 
Les objectifs de cette formation sont :
- Découvrir les principales fonctionnalités des outils [MFront](https://tfel.sourceforge.net/) et [MTest](https://tfel.sourceforge.net/mtest.html) ;
- Apprendre à développer/compiler un modèle de comportement simple sur `MFront` ;
- Utiliser l'outil `MTest` (premiers cas-tests, débogage) ;
- Réaliser des calculs sur structure (lien Code_Aster/MFront).

### Organisation
- __11/10 Matin__
    - Introduction aux principes de `MFront` et aux propriétés matériaux *(M. Wangermez)*
    - Généralités sur les ldc mécaniques, le `DSL Implicit` et la brique `StandardElasticity` *(T. Helfer)*
- __11/10 Après-Midi__
    - *Intégration de lois de comportement simples, utilisation de `MTest` pour les premiers cas-test (point matériel) et le débogage; utilisation de `@CompareToNumericalJacobian`, mode debug, etc... (T. Helfer, M. Wangermez, S. Raude)*
- __12/10 Matin__
    - *Finalisation de l'intégration des lois de comportement proposées, variantes (T. Helfer, M. Wangermez, S. Raude)*
- __12/10 Après-Midi__
    - *Point rapide sur l'interface entre Code_Aster et MFront, MGIS, etc... (T. Helfer, M. Wangermez, J. Dalphin, S. Raude)*
    - *Calcul sur structure (S. Raude)*

### Contenu de ce dépôt
- `hmc-criterion-python-scripts`

    > *Répertoire contenant un notebook jupyter présentant le critère de plasticité utilisé dans les lois de comportement étudiées.*

- `mfront-src-files`

    > *Répertoire contenant les fichiers sources des lois de comportement étudiées.*