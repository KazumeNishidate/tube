

# Nanotube maker

[Kazume_NISHIDATE](kazume.nishidate@gmail.com)

-------------------------------------------------------------------------------

### How to use.

  The 'program' directory contains the nanotube makers for Carbon NT, h-BN NT, MoS$_2$ NT, and WS$_2$ NT [1-7].

  Type 'make' and run the code with the `./mktb` command in these directories. 
  
  If you encounter a 'multiple definition error' during the GCC compilation, you can avoid it by adding the option '-z muldefs' in the Makefile.

  The setup.c file defines the Chiral index (n,m)=(10,4).

> tb.n =  10;

> tb.m =  4;
  
  You can generate (n, m) nanotube atomic coordinates by redefining the above index number.

  
  The output file 'fig*vasp' is the atomic coordinates in VASP format. You can visualize these using the code [VESTA](https://jp-minerals.org/vesta/jp/).

- fig1_sandbox.vasp : initial graphene sheet
- fig2_Ch-T-vectors.vasp : Chiral and translational vectors
- fig3_rotated-wall.vasp : rotated graphene 
- fig4_cutout.vasp : cutout the graphene to make a wall of the tube
- fig5_tube.vasp : (n,m) nanotube 

The file QE.in contains the atomic coordinates definition for the [Quantum_ESPRESSO](https://www.quantum-espresso.org/), which can be visualized using the [XCRYSDEN](http://www.xcrysden.org/).

The directory 'examples' contains input files for QE and the band structures of nanotubes where this program generated the atomic coordinates. Note that some of the 'metallic' carbon nanotubes with small diameters open small energy gaps because of their steep curvature [1,2]. You should manually optimize the supercell size of the CELL_PARAMETERS section of QE input files to maintain accuracy and computational costs, especially for large-radius NTs, since the LX and LY are automatically set as four times larger than their radius. Also, structural relaxations should be performed for nanotubes before the band structure calculations. 
  
You can refer to the Sec. 7.2 of the book, [C言語によるコンピュータシミュレーション](http://web.cc.iwate-u.ac.jp/~nisidate/main.pdf) (Japanese), for more detail.
  
**Reference**

[1] S. Reich, C. Thomsen, and P. Ordej&oacute;n, Phys. Rev. B, 65, 155411 (2002).
[https://doi.org/10.1103/PhysRevB.65.155411](https://doi.org/10.1103/PhysRevB.65.155411)

[2] V. Z&oacute;lyomi and J. K&uuml;riti, Phys. Rev. B, 70, 085403 (2004).
[https://doi.org/10.1103/PhysRevB.70.085403](https://doi.org/10.1103/PhysRevB.70.085403)

[3] C. Jin, F. Lin, K. Suenaga, and S. Iijima, Phys. Rev Lett. 102, 195505 (2009).
[https://doi.org/10.1103/PhysRevLett.102.195505](https://doi.org/10.1103/PhysRevLett.102.195505)

[4] G. Y. Guo and J. C. Lin, Phys. Rev. B, 71, 165402 (2005).
[https://doi.org/10.1103/PhysRevB.71.165402](https://doi.org/10.1103/PhysRevB.71.165402)

[4] G. Y. Guo and J. C. Lin, Phys. Rev. B, 71, 165402 (2005).
[https://doi.org/10.1103/PhysRevB.71.165402](https://doi.org/10.1103/PhysRevB.71.165402)

[5] G. Seifert, H. Terrones, M. Terrones, G. Jungnickel, and T. Frauenheim, Phys. Rev. Lett, 85, 146 (2000).
[https://doi.org/10.1103/PhysRevLett.85.146](https://doi.org/10.1103/PhysRevLett.85.146)

[6] J. Xiao, M. Long, X. Li, H. Xu, H. Huang, and Y. Gao, Sci. Rep. 4, 4327 (2014).
[https://doi.org/10.1038/srep04327](https://doi.org/10.1038/srep04327)

[7] M. Ghorbani-Asl, N. Zibounche, M. Wahiduzzaman, A. F. Oliveira, A. Kuc, and T. Heine, Sci. Rep. 3, 2961 (2013).
[https://doi.org/10.1038/srep02961](https://doi.org/10.1038/srep02961)
