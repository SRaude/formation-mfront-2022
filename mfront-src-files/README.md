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
F \coloneqq \frac{I_1}{3}\sin{\varphi} + \sqrt{J_2K_{F,m}^2+a^2\sin^2{\varphi}}-C\cos{\varphi} \le 0
$$

${I_1=\sigma_{kk}}$ est le premier invariant du tenseur des contraintes, ${J_2=\frac{1}{2}\left(\boldsymbol{\sigma_d}:\boldsymbol{\sigma_d}\right)}$ est le second invariant du déviateur des contraintes ${\boldsymbol{\sigma_d}=\mathbb{K}:\boldsymbol{\sigma}}$. ${C>0}$ et ${\varphi>0}$ représentent respectivement la cohésion du matériau et son angle de frottement interne. ${a\in\left]0,\frac{C}{\tan{\varphi}}\right]}$ est un paramètre qui contrôle l'intersection du critère avec l'axe hydrostatique&nbsp;-&nbsp;défini par ${\sigma_{eq}=\sqrt{3J_2}\equiv 0}$. $K_m$ est déterminé de manière à ce que $F$ représente un *cône hyperbolique* inscrit dans la pyramide *classique* de Mohr-Coulomb (cf. cercle bleu pour ${\gamma=0}$ en haut à gauche de la figure  [[fig1]](https://github.com/SRaude/formation-mfront-2022/blob/main/hmc-criterion-python-scripts/hyperbolic_mc_fp_pi_plane_min.pdf)),

$$
K_{F,m}=cos(\theta_{F,m})-\frac{1}{\sqrt{3}}\sin{\theta_{F,m}}\sin{\varphi},\qquad \theta_{F,m}=\tan^{-1}\left(\frac{-\sin{\varphi}}{\sqrt{3}}\right)
$$

L'influence des paramètres $C$, $\varphi$, et $a$ sur le critère $F$ est présentée sur les figures [[fig1]](https://github.com/SRaude/formation-mfront-2022/blob/main/hmc-criterion-python-scripts/hyperbolic_mc_fp_pi_plane_min.pdf) et [[fig2]](https://github.com/SRaude/formation-mfront-2022/blob/main/hmc-criterion-python-scripts/hyperbolic_mc_fp_stress_plane_min.pdf).

### Potentiel plastique

Afin de reproduire plus fidèlement le développement de la dilatance dans les géomatériaux, le potentiel plastique diffère quelque peu du critère de plasticité $F$. Il garde néanmoins la même structure,

$$
G \coloneqq \frac{I_1}{3}\sin{\psi} + \sqrt{J_2K_{G,m}^2+a_G^2\sin^2{\psi}}-C\cos{\psi} \le 0
$$

${\psi>0}$ est l'angle de dilatance. ${a_G=a\frac{\tan{\varphi}}{\tan{\psi}}}$. $K_{G,m}$ est le pendant de $K_{F,m}$,

$$
K_{G,m}=cos(\theta_{G,m})-\frac{1}{\sqrt{3}}\sin{\theta_{G,m}}\sin{\psi},\qquad \theta_{G,m}=\tan^{-1}\left(\frac{-\sin{\psi}}{\sqrt{3}}\right)
$$

### Écoulement plastique

La direction d'écoulement plastique est donnée par la dérivée de $G$ par rapport à $\boldsymbol{\sigma}$,

$$
\boldsymbol{n_G} = \frac{\partial G}{\partial\boldsymbol{\sigma}} = \frac{\partial G}{\partial I_1} \frac{\partial I_1}{\partial\boldsymbol{\sigma}} + \frac{\partial G}{\partial J_2} \frac{\partial J_2}{\partial\boldsymbol{\sigma}}
$$

Avec,

$$
\begin{cases}
\frac{\partial G}{\partial I_1} = \frac{\sin{\psi}}{3}\\
\frac{\partial G}{\partial J_2} = \frac{K_{G,m}^2}{2R_G},\qquad R_G=\sqrt{J_2K_{G,m}^2+a_G^2\sin^2{\psi}}\\
\frac{\partial I_1}{\partial\boldsymbol{\sigma}} = \boldsymbol{\delta}\\
\frac{\partial J_2}{\partial\boldsymbol{\sigma}} = \boldsymbol{\sigma_d}\\
\end{cases}
$$

L'incrément de déformation plastique est donné par

$$
\boldsymbol{\dot{\epsilon}^p} = \dot{\lambda} \boldsymbol{n_G}
$$

L'incrément de déformation volumique plastique est donné par

$$
{\dot{\epsilon}}_{v}^{p} = {\dot{\lambda}}\sin{\psi}
$$

### Intégration numérique

Les équations présentées ci-dessus sont intégrées par un schéma implicite [standard](https://tfel.sourceforge.net/implicit-dsl.html).

#### Chargement plastique

##### Système implicite d'équations à résoudre

En charge plastique, le système d'équations à résoudre se met sous la forme suivante,

$$
\begin{cases}
\boldsymbol{f_{\boldsymbol{\epsilon^e}}} \equiv \boldsymbol{\Delta\epsilon^{e}} - \boldsymbol{\Delta\epsilon} + \Delta\lambda\boldsymbol{n_G}^{t+\theta\Delta t} = 0\\
f_\lambda \equiv \frac{F}{E} = 0
\end{cases}
$$

En pratique, $\theta$ sera tout le temps pris égal à 1. Les inconnues du système sont ${\boldsymbol{\Delta\epsilon^e}}$, incrément du tenseur des déformations élastiques, et ${\Delta\lambda}$, incrément du multiplicateur plastique.

##### Calcul du jacobien du système à résoudre

Le jacobien du système implicite à résoudre se décompose par blocs,

$$
J = \begin{pmatrix}
\frac{\partial \boldsymbol{f_{\boldsymbol{\epsilon^e}}}}{\partial\boldsymbol{\Delta\epsilon^e}} & \frac{\partial \boldsymbol{f_{\boldsymbol{\epsilon^e}}}}{\partial\Delta\lambda}\\
\frac{\partial f_{\lambda}}{\partial\boldsymbol{\Delta\epsilon^e}} & \frac{\partial f_{\lambda}}{\partial\Delta\lambda}
\end{pmatrix}
$$

Les deux blocs de la première ligne s'écrivent,

$$
\begin{cases}
\frac{\partial \boldsymbol{f_{\boldsymbol{\epsilon^e}}}}{\partial\boldsymbol{\Delta\epsilon^e}} = \mathbb{I} + \Delta\lambda\left(\frac{\partial \boldsymbol{n_G}}{\partial\boldsymbol{\sigma}}:\mathbb{C}\right)\\
\frac{\partial \boldsymbol{f_{\boldsymbol{\epsilon^e}}}}{\partial\Delta\lambda} = \boldsymbol{n_G}
\end{cases}
$$

Avec,

$$
\frac{\partial \boldsymbol{n_G}}{\partial\boldsymbol{\sigma}} = \frac{\partial^2 G}{\partial J_2^2} \left(\boldsymbol{\sigma_d}\otimes \boldsymbol{\sigma_d}\right) + \frac{\partial G}{\partial J_2} \mathbb{K},\qquad \frac{\partial^2 G}{\partial J_2^2} = -\frac{K_{G,m}}{2R_G^2} \frac{\partial G}{\partial J_2}
$$

Les deux blocs de la seconde ligne s'écrivent,

$$
\begin{cases}
\frac{\partial f_{\lambda}}{\partial\boldsymbol{\Delta\epsilon^e}} = \frac{1}{E}\left(\frac{\partial F}{\partial\boldsymbol{\sigma}}:\mathbb{C}\right)\\
\frac{\partial f_{\lambda}}{\partial\Delta\lambda} = 0
\end{cases}
$$

Avec,

$$
\frac{\partial F}{\partial\boldsymbol{\sigma}} = \frac{\partial F}{\partial I_1} \frac{\partial I_1}{\partial\boldsymbol{\sigma}} + \frac{\partial F}{\partial J_2} \frac{\partial J_2}{\partial\boldsymbol{\sigma}},\qquad
\frac{\partial F}{\partial I_1} = \frac{\sin{\varphi}}{3},\qquad
\frac{\partial F}{\partial J_2} = \frac{K_{F,m}^2}{2R_F},\qquad R_F=\sqrt{J_2K_{F,m}^2+a^2\sin^2{\varphi}}\\
$$

#### Chargement élastique

En charge élastique, le système d'équations à résoudre se met sous la forme suivante,

$$
\begin{cases}
\boldsymbol{f_{\boldsymbol{\epsilon^e}}} \equiv \boldsymbol{\Delta\epsilon^{e}} - \boldsymbol{\Delta\epsilon} = 0\\
f_\lambda \equiv \Delta\lambda = 0
\end{cases}
$$

Dans ce cas, le jacobien du système est la matrice identité.
