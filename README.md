

# tube

[Kazume_NISHIDATE](kazume.nishidate@gmail.com)

-------------------------------------------------------------------------------

### How to use.

  The **tube** generates atomic positions of various nanotubes, such as carbon nanotube, h-BN, MoS$_2$, WS$_2$, and TiO$_2$ anatase (101) nanotubes [1-8].

  Type `make` and run the code with the `./mktb` command in the directories. 
  
  The setup.c file defines the Chiral index (n,m)=(10,4).

> tb.n =  10;
> tb.m =  4;
  
  You can generate (n, m) nanotube atomic coordinates by redefining the above index number.

  The output file 'fig...vasp' is the atomic coordinates in VASP format. You can visualize these using the [VESTA](https://jp-minerals.org/vesta/jp/).

- **fig1_sandbox.vasp** : initial graphene sheet
- **fig2_Ch-T-vectors.vasp** : Chiral and translational vectors
- **fig3_rotated-wall.vasp** : rotated graphene 
- **fig4_cutout.vasp** : cutout the graphene to make a wall of the tube
- **fig5_tube.vasp** : (n,m) nanotube 

The file OMX.dat is the data file for the [OpenMX](https://www.openmx-square.org/), while the file QE.in is for the [QuantumESPRESSO](https://www.quantum-espresso.org/). Examples of band-structure calculations are saved in the `omx-ex` and `qe-ex` directories.

- Some of the *metallic* carbon nanotubes with small diameters open small energy gaps because of their steep curvature [1,2].

- You should manually optimize the supercell size to maintain accuracy and computational efficiency, especially for large-radius nanotubes, since the supercell dimensions are automatically set to 4 times the nanotube radius.
  
- The `c-nt` directory contains a small Perl script, **reset-positions.pl** which resets the supercell dimensions as well as the axial position of the nanotube. 

- Structural relaxations should be performed on *some* nanotubes before conducting band structure calculations. In our experiences, this procedure was quite essential for the anatase nanotubes.




  
If you encounter a `multiple definition error` during the GCC compilation, you can avoid it by adding the compile option `-z muldefs`  in the Makefile.

  
You can refer to the Sec. 7.2 of the book, [Computer simulation with C](http://web.cc.iwate-u.ac.jp/~nisidate/main.pdf) (Japanese), for more detail.
  
**Reference**

[1] S. Reich, C. Thomsen, and P. Ordej&oacute;n, Phys. Rev. B, 65, 155411 (2002).
[https://doi.org/10.1103/PhysRevB.65.155411](https://doi.org/10.1103/PhysRevB.65.155411)

[2] V. Z&oacute;lyomi and J. K&uuml;riti, Phys. Rev. B, 70, 085403 (2004).
[https://doi.org/10.1103/PhysRevB.70.085403](https://doi.org/10.1103/PhysRevB.70.085403)

[3] C. Jin, F. Lin, K. Suenaga, and S. Iijima, Phys. Rev Lett. 102, 195505 (2009).
[https://doi.org/10.1103/PhysRevLett.102.195505](https://doi.org/10.1103/PhysRevLett.102.195505)



[4] G. Y. Guo and J. C. Lin, Phys. Rev. B, 71, 165402 (2005).
[https://doi.org/10.1103/PhysRevB.71.165402](https://doi.org/10.1103/PhysRevB.71.165402)

[5] G. Seifert, H. Terrones, M. Terrones, G. Jungnickel, and T. Frauenheim, Phys. Rev. Lett, 85, 146 (2000).
[https://doi.org/10.1103/PhysRevLett.85.146](https://doi.org/10.1103/PhysRevLett.85.146)

[6] J. Xiao, M. Long, X. Li, H. Xu, H. Huang, and Y. Gao, Sci. Rep. 4, 4327 (2014).
[https://doi.org/10.1038/srep04327](https://doi.org/10.1038/srep04327)

[7] M. Ghorbani-Asl, N. Zibounche, M. Wahiduzzaman, A. F. Oliveira, A. Kuc, and T. Heine, Sci. Rep. 3, 2961 (2013).
[https://doi.org/10.1038/srep02961](https://doi.org/10.1038/srep02961)

[8] Francesca Nunzi and Filippo De Angelis, J. Phys. Chem C, 115, 2179 (2011).
[https://pubs.acs.org/doi/abs/10.1021/jp110132k](https://pubs.acs.org/doi/abs/10.1021/jp110132k)

