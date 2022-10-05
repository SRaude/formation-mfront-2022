# Formation MFront (EDF-ERMES/MMC) 2022
### Contenu de la formation 
Les objectifs de cette formation sont :
- Découvrir les principales fonctionnalités des outils [MFront](https://tfel.sourceforge.net/) et [MTest](https://tfel.sourceforge.net/mtest.html) ;
- Apprendre à développer/compiler un modèle de comportement simple sur `MFront` ;
- Utiliser l'outil `MTest` (premiers cas-tests, débogage) ;
- Réaliser des calculs sur structure (lien Code_Aster/MFront).

### Organisation de ces deux jours de formation
- __11/10 AM__
    > Introduction aux principes de `MFront` et aux propriétés matériaux --- __M. Wangermez__.
    Généralités sur les lois de comportement mécaniques, le `DSL Implicit` et la brique `StandardElasticity` --- __T. Helfer__
- __11/10 PM__
    > Intégration de lois de comportement simples, utilisation de `MTest` pour les premiers cas-test (point matériel) et le débogage (utilisation de `@CompareToNumericalJacobian`, mode debug, etc...) --- __T. Helfer, M. Wangermez, S. Raude__
- __12/10 AM__
    > Finalisation de l'intégration des lois de comportement proposées, variantes --- __T. Helfer, M. Wangermez, S. Raude__
    Point rapide sur l'interface entre Code_Aster et MFront, MGIS, ... --- __T. Helfer, M. Wangermez, J. Dalphin, S. Raude__
- __12/10 PM__
    > Cas de calcul sur structure (`Code_Aster` + `MFront`) --- __S. Raude__

### Contenu de ce dépôt
- `hmc-criterion-python-scripts` - répertoire contenant un notebook jupyter présentant le critère de plasticité utilisé dans les lois de comportement proposées ;
- `mfront-src-files` - répertoire contenant les fichiers sources des lois de comportement à intégrer ;