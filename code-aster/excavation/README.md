# Excavation d'une galerie souterraine

## Définition du problème

L'objectif est de modéliser le creusement d'une galerie souterraine (tunnel) dans une *roche* située à $490$&nbsp;m de profondeur. Le domaine d'étude est réduit de moitié par symétrie d'axe $Y$. Le rayon de la galerie est ${R=2.6}$&nbsp;m. La hauteur et la largeur du modèle sont respectivement de ${50R}$ et ${25R}$ (cf. figure ci-dessous). Le calcul est mené sous l'hypothèse des déformations planes (`D_PLAN`) et des petites perturbations (`PETIT`).

<p align="center">
  <img width="100%" src="https://user-images.githubusercontent.com/68728185/194753936-176394b6-6e1f-4f42-9bd3-9c49232ddb9b.png">
</p>

## Conditions aux limites et initiales

Le champ de contrainte initial est *géostatique*, défini par ${\sigma_{XX}=-16.1}$&nbsp;MPa, ${\sigma_{YY}=-12.4}$&nbsp;MPa, et ${\sigma_{ZZ}=-12.7}$&nbsp;MPa au niveau du centre de la galerie. Le champ de déplacement initial est nul. Le champ de déformation initial est déduit de la loi de Hooke. Le scénario de calcul se divise en deux étapes&nbsp;: 1.&nbsp;phase d'équilibre permettant de vérifier la bonne mise en donnée et la récupération des réactions nodales en paroi de galerie, 2.&nbsp;phase d'excavation proprement dite. Le déplacement des frontières verticales est bloqué suivant $X$, i.e ${u_x=0}$. Le déplacement des frontières horizontales est bloqué suivant $Y$, i.e ${u_Y=0}$. Pendant la première phase dite d'équilibre, ${u_X=u_Y=0}$ en paroi de galerie&nbsp;; cette condition permet de récupérer les réactions nodales (ou forces nodales) liées au champ de contrainte initial non-nul. Pendant la phase d'excavation, ces réactions nodales sont progressivement (linéairement) réduites à $0$&nbsp; de manière à modéliser le déconfinement progressif lié à l'excavation de matière (méthode convergence/confinement).

## Matériaux

La réponse mécanique du domaine étudié est modélisée par l'une des lois de comportement dévelopées dans le cadre de cette formation, `MCBigoniMini`, `MCBigoniMiniIH`, `MCBigoniFull`. Les paramètres matériau par défaut sont présentés dans le tableau ci-dessous

<div align="center">
  
| Symbole   | Nom             | Valeur par défaut           | Unité |
|  :------: | :-------------: | :-------------------------: | :---: |
| $E$       | `YoungModulus`  | $9\times 10^9$              | Pa    |
| $\nu$     | `PoissonRatio`  | $0.25$                      | -     |
| $\varphi$ | `FrictionAngle` | $32.07$                     | °     |
| $\psi$    | `DilationAngle` | $32.07$                     | °     |
| $C$       | `Cohesion`      | $4.21\times 10^6$           | Pa    |
| $a$       | `TensionCutOff` | $\frac{C}{20\tan{\varphi}}$ | Pa    |
| $h_c$     | `HardeningCoef` | $0$                         | -     |
| $\gamma$  | `PiShapeCoef`   | $0.99$                      | -     |
 
