# Équations constitutives

## `MCBigoniMini.mfront`

La ldc intégrée dans `MCBigoniMini.mfront` constitue une version simplifiée&nbsp;-&nbsp;indépendante du troisième invariant du déviateur du tenseur des contraintes, $J_3$, ou encore de l'angle de Lode, noté $\theta$&nbsp;-&nbsp;de celle décrite [ici](https://tfel.sourceforge.net/MohrCoulomb.html).

Les équations constitutives de cette version simplifiée sont décrites dans les paragraphes suivants.

### Partition du tenseur des déformations

Le tenseur des déformations se divise en deux composantes&nbsp;; élastique, $\boldsymbol{\epsilon^e}$, et plastique, $\boldsymbol{\epsilon^p}$,

$$
\boldsymbol{\epsilon} = \boldsymbol{\epsilon^e} + \boldsymbol{\epsilon^p}
$$

Nous ferons par ailleurs l'hypothèse des petites transformations&nbsp;; ce qui permet d'écrire,

$$
\boldsymbol{\dot{\epsilon}} = \boldsymbol{\dot{\epsilon}^e} + \boldsymbol{\dot{\epsilon}^p}
$$

### Comportement élastique

Le comportement élastique est supposé linéaire et isotrope. La loi de Hooke s'écrit,

$$
\boldsymbol{\sigma} = \mathbb{C}:\boldsymbol{\epsilon}
$$

Avec,

$$
\mathbb{C}=3K\mathbb{J}+2\mu\mathbb{K},\qquad K=\frac{E}{3\left(1-2\nu\right)},\qquad \mu=\frac{E}{2\left(1+\nu\right)},\qquad \mathbb{J}=\boldsymbol{\delta}\otimes\boldsymbol{\delta},\qquad \mathbb{K}=\mathbb{I}-\mathbb{J}
$$
