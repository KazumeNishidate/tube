# Carbon nanotube maker

[Kazume_NISHIDATE](kazume.nishidate@gmail.com)

-------------------------------------------------------------------------------

### How to use.

  The Chiral index is defined in the setup.c file.

>  tb.n =  10;

>  tb.m =  4;
  
  By defining the above index number, you can generate (n, m) nanotube
  atomic coordinates.
  
  Type the following command
	`make`
  and run the code with
	`./mktb`
  
  The output files, *vasp, are the atomic coordinates files in VASP
  format. You can visualize these using the code
  [VESTA](https://jp-minerals.org/vesta/jp/).
  
- fig1_sandbox.vasp : initial graphen sheet
- fig2_Ch-T-vectors.vasp : Chiral and translational vectors
- fig3_rotated-wall.vasp : rotated graphene 
- fig4_cutout.vasp : cutout the graphene to make a wall of the tube
- fig5_tube.vasp : (n,m) nanotube 
 
  
  The file, QE.in, is the atomic position file for the input file of
  pw.x of [Quantum_ESPRESSO](https://www.quantum-espresso.org/).
  
  
