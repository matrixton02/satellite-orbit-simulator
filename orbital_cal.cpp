#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

const double G=6.67430e-11;
const double M=5.97219e24;
const double mu=G*M;
const double R_earth=6371e3;

double dt=0;
double t=0;

typedef struct pos{
    double x;
    double y;
    double z;
    pos(){
            x=0;
            y=0;
            z=0;
    }
} pos;

typedef struct vel{
    double vx;
    double vy;
    double vz;
    vel(){
        vx=0;
        vy=0;
        vz=0;
    }
} vel;

typedef struct accl{
    double ax;
    double ay;
    double az;
    accl(){
        ax=0;
        ay=0;
        az=0;
    }
}accl;

void initial(pos* p,vel* v){
    int orbital_type=0;
    double r_sat=0;
    double incl=0;

    cout<<"Orbital type:\n";
    cout<<"1.Circular\n2.Elliptical\nEnter your choice: ";
    cin>>orbital_type;

    cout<<"Satellite orbital radius above earth(km): ";
    cin>>r_sat;

    r_sat=r_sat*1000; //convertion of radius of satellite from Km to m

    cout<<"Inclination in degress: ";
    cin>>incl;
    incl=incl*M_PI/180;

    cout<<"Time stamp: ";
    cin>>dt;

    cout<<"Total time: ";
    cin>>t;

    double v_sat=0;
    double a=0;
    double e=0;
    double r_peri=0;
    switch(orbital_type){
        case 1:
            r_sat+=R_earth;

            p->x=r_sat;
            p->y=0;
            p->z=0;

            v_sat=sqrt(mu/r_sat);
            v->vx=0;
            v->vy=v_sat*cos(incl);
            v->vz=v_sat*sin(incl);

        break;

        case 2:
            cout<<"Enter semi_major axis(a) in Km: ";
            cin>>a;
        
            a=a*1000; //conversion from Km to m
            a+=R_earth; // the distance of semi major axis was calculated from earths surface so we added the R_earth to make it form the center of earth

            cout<<"Enter eccentricity of the ellipse(e): ";
            cin>>e;

            r_peri=a*(1-e);

            p->x=r_peri;
            p->y=0;
            p->z=0;

            v_sat=sqrt(mu*(2/r_peri-1/a));
            v->vx=0;
            v->vy=v_sat*cos(incl);
            v->vz=v_sat*sin(incl);
        break;

        default:
            cout<<"Enter a valid input\n";
    }
}

void compute_accl(accl* acc,pos* p,double r){
    acc->ax=-mu*p->x/pow(r,3);
    acc->ay=-mu*p->y/pow(r,3);
    acc->az=-mu*p->z/pow(r,3);
}

double getEnergy(vel* v,double r){
    double E=0.5*(v->vx*v->vx+v->vy*v->vy+v->vz*v->vz)-(mu/r);
    return E;
}

double getAngular(pos* p,vel* v){
    double hx,hy,hz,h=0;

    hx=p->y*v->vz-p->z*v->vy;
    hy=p->z*v->vx-p->x*v->vz;
    hz=p->x*v->vy-p->y*v->vx;

    h=sqrt(hx*hx+hy*hy+hz*hz);
    return h;
}
int main(){
    pos p;
    vel v;
    accl acc;
    initial(&p,&v);
    double time=0;

    ofstream file;
    string filename="data.csv";

    file.open(filename);
    if(!file.is_open()){
        cout<<"Error opening the file...";
    }

    file<<"t,x,y,z,vx,vy,vz,r,E,h\n";

    double r=0;
    double ax_old,ay_old,az_old=0;
    double E=0;
    double h=0;
    r=sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
    compute_accl(&acc,&p,r);
    while(time<t){
        ax_old=acc.ax;
        ay_old=acc.ay;
        az_old=acc.az;
        
        p.x+=v.vx*dt+0.5*ax_old*dt*dt;
        p.y+=v.vy*dt+0.5*ay_old*dt*dt;
        p.z+=v.vz*dt+0.5*az_old*dt*dt;

        r=sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
        compute_accl(&acc,&p,r);

        v.vx+=0.5*(acc.ax+ax_old)*dt;
        v.vy+=0.5*(acc.ay+ay_old)*dt;
        v.vz+=0.5*(acc.az+az_old)*dt;

        E=getEnergy(&v,r);
        h=getAngular(&p,&v);

        file<<time<<","<<p.x<<","<<p.y<<","<<p.z<<","<<v.vx<<","<<v.vy<<","<<v.vz<<","<<r<<","<<E<<","<<h<<"\n";
        time+=dt;
    }
    file.close();
    return 0;
}