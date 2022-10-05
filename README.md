# Formation MFront (EDF-ERMES/MMC) 2022
### Contenu de la formation 
Les objectifs de cette formation sont :
- Découvrir les principales fonctionnalités des outils [MFront](https://tfel.sourceforge.net/) et [MTest](https://tfel.sourceforge.net/mtest.html) ;
- Apprendre à développer/compiler un modèle de comportement simple sur `MFront` ;
- Utiliser l'outil `MTest` (premiers cas-tests, débogage) ;
- Réaliser des calculs sur structure (lien Code_Aster/MFront).

### Organisation de ces deux jours de formation
- 11/10 AM - Introduction aux principes de `MFront` et aux propriétés matériaux (M. Wangermez). Généralités sur les lois de comportement mécaniques, le `DSL Implicit` et la brique `StandardElasticity` (T. Helfer)
- 11/10 PM - Intégration de lois de comportement simples, utilisation de `MTest` (T. Helfer, M. Wangermez, S. Raude)
- 12/10 AM - Finalisation de l'intégration des lois proposées (T. Helfer, M. Wangermez, S. Raude)
- 12/10 PM - Cas de calcul sur structure (`Code_Aster` + `MFront`)

### Contenu de ce dépôt
- `hmc-criterion-python-scripts` - répertoire contenant un notebook jupyter présentant le critère de plasticité utilisé dans les lois de comportement proposées ;
- `mfront-src-files` - répertoire contenant les fichiers sources des lois de comportement à intégrer ;