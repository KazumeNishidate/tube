

# Carbon nanotube maker

[Kazume_NISHIDATE](kazume.nishidate@gmail.com)

-------------------------------------------------------------------------------

### How to use.

  Type 'make' and run the code with the `./mktb` command.

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
  
The file, QE.in, is the atomic coordinates definition for the [Quantum_ESPRESSO](https://www.quantum-espresso.org/).

The directory 'Examples' contains input files for QE and the band structures of (10,0), (10,4), (6,6), (8,0), and (9,3) nanotubes where this program generated the atomic coordinates. Note that some of the 'metallic' nanotubes with small diameters open small energy gaps because of their steep curvature [1,2].
  
You can refer to the Sec. 7.2 of the book, [C言語によるコンピュータシミュレーション](http://web.cc.iwate-u.ac.jp/~nisidate/main.pdf) (Japanese), for more detail.
  
**Reference**

[1] S. Reich, C. Thomsen, P. Ordej&oacute;n, Phys. Rev. B, 65, 155411 (2002).
[https://doi.org/10.1103/PhysRevB.65.155411](https://doi.org/10.1103/PhysRevB.65.155411)

[2] V. Z&oacute;lyomi and J. K&uuml;riti, Phys. Rev. B, 70 085403 (2004).
[https://doi.org/10.1103/PhysRevB.70.085403](https://doi.org/10.1103/PhysRevB.70.085403)
