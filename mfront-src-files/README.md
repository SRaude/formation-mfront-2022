# Équations constitutives

## MCBigoniMini

La ldc intégrée dans `MCBigoniMini.mfront` constitue une version simplifiée&nbsp;-&nbsp;indépendante du troisième invariant du déviateur des contraintes, $J_3$, ou encore de l'angle de Lode, noté $\theta$&nbsp;-&nbsp;de celle décrite [ici](https://tfel.sourceforge.net/MohrCoulomb.html).

Les équations constitutives de cette version simplifiée sont décrites dans les paragraphes suivants.

### Partition du tenseur des déformations

Le tenseur des déformations, $\boldsymbol{\epsilon}$ se divise en deux composantes&nbsp;; la première élastique, $\boldsymbol{\epsilon^e}$, la seconde plastique, $\boldsymbol{\epsilon^p}$,

$$
\boldsymbol{\epsilon} = \boldsymbol{\epsilon^e} + \boldsymbol{\epsilon^p}
$$

Nous ferons par ailleurs l'Hypothèse des Petites Perturbations (HPP)&nbsp;; ce qui permet d'écrire,

$$
\boldsymbol{\dot{\epsilon}} = \boldsymbol{\dot{\epsilon}^e} + \boldsymbol{\dot{\epsilon}^p}
$$

### Comportement élastique

Le comportement élastique est supposé *linéaire* et *isotrope*. La loi de Hooke s'écrit,

$$
\boldsymbol{\sigma} = \mathbb{C}:\boldsymbol{\epsilon}
$$

Avec,

$$
\mathbb{C}=3K\mathbb{J}+2\mu\mathbb{K},\qquad K=\frac{E}{3\left(1-2\nu\right)},\qquad \mu=\frac{E}{2\left(1+\nu\right)},\qquad \mathbb{J}=\frac{1}{3}\boldsymbol{\delta}\otimes\boldsymbol{\delta},\qquad \mathbb{K}=\mathbb{I}-\mathbb{J}
$$

${E>0}$ est le module de Young, ${\nu\in\left]-1,0.5\right[}$ est le coefficient de Poisson, ${K>0}$ est le module de compressibilité, ${\mu>0}$ est le module de cisaillement, $\mathbb{C}$ est le tenseur de Hooke, $\mathbb{J}$ et $\mathbb{K}$ sont respectivement les projecteurs sphérique et déviatorique d'ordre 4, et $\boldsymbol{\sigma}$ est le tenseur des contraintes.

### Critère de plasticité

Le critère de plasticité, $F$, est de type Mohr-Coulomb généralisé,

$$
F = \frac{I_1}{3}\sin{\varphi} + \sqrt{J_2K_m^2+a^2\sin^2{\varphi}}-C\cos{\varphi} \le 0
$$

${I_1=\sigma_{kk}}$ est le premier invariant du tenseur des contraintes, ${J_2=\frac{1}{2}\left(\boldsymbol{\sigma_d}:\boldsymbol{\sigma_d}\right)}$ est le second invariant du déviateur des contraintes ${\boldsymbol{\sigma_d}=\mathbb{K}:\boldsymbol{\sigma}}$. $C$ et $\varphi$ sont respectivement la cohésion du matériau et son angle de frottement interne. ${a\in\left]0,\frac{C}{\tan{\varphi}}\right]}$ est un paramètre qui contrôle l'intersection du critère avec l'axe hydrostatique défini par ${\sigma_{eq}=\sqrt{3J_2}\equiv 0}$. $K_m$ est déterminé de manière à ce que $F$ représente un *cône hyperbolique* inscrit dans la pyramide *classique* de Mohr-Coulomb (cf. cercle bleu pour ${\gamma=0}$ en haut à gauche de cette [fig.](https://github.com/SRaude/formation-mfront-2022/blob/main/hmc-criterion-python-scripts/hyperbolic_mc_fp_pi_plane_min.pdf)),

$$
K_m=cos(\theta_m)-\frac{1}{\sqrt{3}}\sin{\theta_m}\sin{\varphi},\qquad \theta_m=\tan^{-1}\left(\frac{-\sin{\varphi}}{\sqrt{3}}\right)
$$
