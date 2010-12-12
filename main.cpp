#include "PetriSim.h"

int main(int argc,const char* argv[])
{

	/*SCCalendar* cal = new SCCalendar();
	SCBase base3, base1, base2;
	cal->Insert(&base3, 2.0);
	cal->Insert(&base1, 3.0);
	cal->Insert(&base2, 1.0);
	SCBase base;// = new SCPlace();
	SCCalendarUnit unit(&base,5.0);
	cal->Insert(unit);
	cal->Show();
	cout<<"....p...."<<cal->GetNextUnit().GetTime()<<endl;
	cal->Remove();
	cal->Show();
         */
    /*
    //model cvicenie 1, slidy strana 12, horny obrazok
	SCPlace p[5];
	SCDirectedArc a[8];
	SCTransition t[3];

	p[0].SetArgStartVal(1);
	p[1].SetArgStartVal(1);

	PlToTr(&p[0],&t[0],&a[0]);
	TrToPl(&t[0],&p[2],&a[1]);
	PlToTr(&p[1],&t[0],&a[2]);
	PlToTr(&p[2],&t[1],&a[3]);
	TrToPl(&t[1],&p[3],&a[4]);
	PlToTr(&p[3],&t[2],&a[5]);
	TrToPl(&t[2],&p[1],&a[6]);
	TrToPl(&t[2],&p[4],&a[7]);
          */
/*
	//model cvicenie 1, slidy strana 12, dolny obrazok
	SCPlace p[4];
	SCDirectedArc a[6];
	SCTransition t[3];

	p[0].SetArgStartVal(1);
	
	PlToTr(&p[0],&t[0],&a[0]);
	TrToPl(&t[0],&p[1],&a[1]);
	TrToPl(&t[1],&p[2],&a[2]);
	PlToTr(&p[2],&t[2],&a[3]);
	TrToPl(&t[2],&p[3],&a[4]);
	PlToTr(&p[0],&t[2],&a[5]);
*/
	SCPlace p[3];
	SCDirectedArc a[4];
	SCTransition t[2];

	p[0].SetArgStartVal(2);
	t[0].SetArgProbability(70);

	PlToTr(&p[0],&t[0],&a[0]);
	PlToTr(&p[0],&t[1],&a[1]);
	TrToPl(&t[0],&p[1],&a[2]);
	TrToPl(&t[1],&p[2],&a[3]);



	g_allPlaces;

	Run();
	PrintStat();
	return 0;
}
