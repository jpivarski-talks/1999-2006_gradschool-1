(sig[0] = {{1,0},{0,1}}) // MatrixForm

Out[15]//MatrixForm= 1   0

                     0   1

(sig[1] = {{0,1},{1,0}}) // MatrixForm

Out[16]//MatrixForm= 0   1

                     1   0

(sig[2] = {{0,-I},{I,0}}) // MatrixForm

Out[17]//MatrixForm= 0    -I

                     I    0

(sig[3] = {{1,0},{0,-1}}) // MatrixForm

Out[18]//MatrixForm= 1    0

                     0    -1

(gam[0] = {{0,0,1,0}, {0,0,0,1}, {1,0,0,0}, {0,1,0,0}}) // MatrixForm

Out[22]//MatrixForm= 0   0   1   0

                     0   0   0   1

                     1   0   0   0

                     0   1   0   0

(gam[1] = {{0,0,0,1}, {0,0,1,0}, {0,-1,0,0}, {-1,0,0,0}}) // MatrixForm

Out[23]//MatrixForm= 0    0    0    1

                     0    0    1    0

                     0    -1   0    0

                     -1   0    0    0

(gam[2] = {{0,0,0,-I}, {0,0,I,0}, {0,I,0,0}, {-I,0,0,0}}) // MatrixForm

Out[24]//MatrixForm= 0    0    0    -I

                     0    0    I    0

                     0    I    0    0

                     -I   0    0    0

(gam[3] = {{0,0,1,0}, {0,0,0,-1}, {-1,0,0,0}, {0,1,0,0}}) // MatrixForm

Out[25]//MatrixForm= 0    0    1    0

                     0    0    0    -1

                     -1   0    0    0

                     0    1    0    0

{{0,1,0,0} . gam[0] . gam[0] . {0,1,0,0}, 
 {0,1,0,0} . gam[0] . gam[1] . {0,1,0,0},
 {0,1,0,0} . gam[0] . gam[2] . {0,1,0,0},
 {0,1,0,0} . gam[0] . gam[3] . {0,1,0,0}}

Out[26]= {1, 0, 0, 1}

{{0,1,0,0} . gam[0] . gam[0] . {0,0,1,0}, 
 {0,1,0,0} . gam[0] . gam[1] . {0,0,1,0},
 {0,1,0,0} . gam[0] . gam[2] . {0,0,1,0},
 {0,1,0,0} . gam[0] . gam[3] . {0,0,1,0}}

Out[27]= {0, 0, 0, 0}

{{0,0,1,0} . gam[0] . gam[0] . {0,0,1,0}, 
 {0,0,1,0} . gam[0] . gam[1] . {0,0,1,0},
 {0,0,1,0} . gam[0] . gam[2] . {0,0,1,0},
 {0,0,1,0} . gam[0] . gam[3] . {0,0,1,0}}

Out[28]= {1, 0, 0, 1}

{{0,0,1,0} . gam[0] . gam[0] . {0,1,0,0}, 
 {0,0,1,0} . gam[0] . gam[1] . {0,1,0,0},
 {0,0,1,0} . gam[0] . gam[2] . {0,1,0,0},
 {0,0,1,0} . gam[0] . gam[3] . {0,1,0,0}}

Out[29]= {0, 0, 0, 0}

gam[0] . gam[0] // MatrixForm

Out[31]//MatrixForm= 1   0   0   0

                     0   1   0   0

                     0   0   1   0

                     0   0   0   1

gam[0] . gam[3] // MatrixForm

Out[32]//MatrixForm= -1   0    0    0

                     0    1    0    0

                     0    0    1    0

                     0    0    0    -1

pone[0] = em;
pone[1] = p1;
pone[2] = p2;
pone[3] = p3;
ptwo[0] = em;
ptwo[1] = -p1;
ptwo[2] = -p2;
ptwo[3] = -p3;

pone[0]*sig[0] + pone[1]*sig[1] + pone[2]*sig[2] + pone[3]*sig[3] // MatrixForm

Out[38]//MatrixForm= em + p3     p1 - I p2

                     p1 + I p2   em - p3

Eigenvalues[pone[0]*sig[0] + pone[1]*sig[1] + pone[2]*sig[2] + pone[3]*sig[3]]

                      2     2     2               2     2     2
Out[41]= {em - Sqrt[p1  + p2  + p3 ], em + Sqrt[p1  + p2  + p3 ]}

Eigenvalues[pone[0]*sig[0] - pone[1]*sig[1] - pone[2]*sig[2] - pone[3]*sig[3]]

                      2     2     2               2     2     2
Out[42]= {em - Sqrt[p1  + p2  + p3 ], em + Sqrt[p1  + p2  + p3 ]}

Exit

[Mathematica finished.]
