//
// Created by Quentin on 06/03/2022.
//

#ifndef PROJET_UTILE_H
#define PROJET_UTILE_H
int unionPratique(int x,int y);
int interPratique(int x,int y);
int puissance(int puiss);
int logarithme(int x);
int appartienPratique(int tenir, int appartien);
int RS1Pratique(int x, int y, int rkMinx, int rkMiny, bool continueSat);
int RS2Pratique(int x, int y, int rkMiny, int rkMinx, bool continueSat);
int RS3Pratique(int x, int y, int rkMaxy, int rkMaxx, bool continueSat);
int RS4Pratique(int x, int y, int rkMaxy, int rkMaxx, bool continueSat);
int RS5Pratique(int rkMaxx, int rkMaxy,int rkMinunion, int rkMaxinter, bool continueSat);
int RS6Pratique(int rkMaxx, int rkMaxy,int rkMininter, int rkMaxunion, bool continueSat);
int RS7Pratique(int rkMinunion, int rkMininter,int rkMaxy, int rkMinx, bool continueSat);
int RS8Pratique(int rkMinunion, int rkMininter,int rkMaxx, int rkMiny, bool continueSat);

#endif //PROJET_UTILE_H
