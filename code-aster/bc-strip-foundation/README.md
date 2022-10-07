# Calcul de la capacité portante d'un sol soumis à la charge d'une fondation superficielle

## Définition du problème

L'objectif est de déterminer la *capacité portante d'un sol* soumis à un chargement vertical appliqué à une fondation superficielle rigide (cas-test de validation Code_Aster `ssnp104`). Le domaine considéré a une largeur de $60$&nbsp;m et une hauteur de $20$&nbsp;m. Le calcul est mené sous l'hypothèse des déformations planes, `D_PLAN`, et des petites perturbations, `PETIT`. Par symétrie d'axe $Y$, le domaine étudié est réduit de moitié suivant $X$. La fondation a une largeur totale de $2$&nbsp;m (réduite à $1$&nbsp;m par symétrie). La semelle n'est pas explicitement représentée dans le modèle&nbsp;; un chargement vertical sera appliqué en surface sur un groupe de noeuds préalablement défini. Le domaine étudié est présenté sur la figure ci-dessous.

<p align="center">
  <img width="50%" src="https://user-images.githubusercontent.com/68728185/194474070-91ea2f9a-ea4f-4d08-a7fe-c0074b4608b8.png">
</p>

## Conditions aux limites et initiales

Une phase d'équilibre précède la phase de chargement de la semelle. Pendant cette première étape, les déplacements, contraintes, et variables internes, s'équilibrent avec le champ de pesanteur ambiant. Cette première phase de résolution sert essentiellement à créer un champ de contrainte initial non nul en équilibre avec le champ de déformation élastique correspondant. L'état initial de la deuxième phase de chargement est donné dans le mot-clé `ETAT_INIT`. Le chargement de la semelle est modélisé par une augmentation du déplacement vertical sur un groupe de noeuds de largeur 1&nbsp;m. $u_Y$ augmente de $0$ à $30$&nbsp;cm en un temps arbitraire de $1$&nbsp;s. Au cours de ces deux étapes de calcul, ${u_X=0}$ sur les frontières verticales et ${u_Y=0}$ sur la frontière horizontale inférieure du domaine considéré.

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
 
</div>

## Solutions de référence

Pour ${\varphi=\psi}$, deux solutions de références sont disponibles dans la littérature&nbsp;; celle de Prandtl, et celle de Terzaghi (cas limite).

### Solution de Prandtl

Le mode de rupture est présenté sur la figure ci-dessous,

<p align="center">
  <img width="60%" src="https://user-images.githubusercontent.com/68728185/194495658-cd6e671d-c297-4407-b7d7-9c3c0abe4275.png">
</p>

La charge limite admissible est donnée par,

$$
q_u = \frac{C}{\tan{\varphi}} \left[ \tan^2{\left( \frac{\pi}{4} + \frac{\varphi}{2} \right)} e^{\pi\tan{\varphi}} - 1 \right] = 300.6\ \text{MN/m}
$$

### Solution de Terzaghi

Le mode de rupture est présenté sur la figure ci-dessous,

<p align="center">
  <img width="60%" src="https://user-images.githubusercontent.com/68728185/194498016-27334df6-628b-455b-b017-9308e072b6b1.png">
</p>

La charge limite admissible est donnée par,

$$
q_u = \frac{1}{2} \gamma b^2 N_\gamma + qbN_q + cbN_c = 308.8\ \text{MN/m}
$$

Avec,

$$
\begin{cases}
N_q = e^{\pi\tan{\varphi}}\left(\frac{1+\sin{\varphi}}{1-\sin{\varphi}}\right)\\
N_\gamma = \frac{1}{4}{\left[ \left(N_q - 1\right)\cos{\varphi} \right]}^{\frac{3}{2}}\\
N_c = \frac{N_q - 1}{\tan{\varphi}}
\end{cases}
$$

## Post-traitement
