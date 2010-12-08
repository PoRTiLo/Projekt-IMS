#include "PetriSim.h"

int main(int argc,const char* argv[])
{

	SCCalendar* cal = new SCCalendar();
	SCPlace p3, p1, p2;
	cal->insert(p3, 2.0);
	cal->insert(p1, 3.0);
	cal->insert(p2, 1.0);
	SCPlace place;// = new SCPlace();
	SCCalendarUnit unit(&place,5.0);
	cal->insert(unit);
	cal->show();
	cout<<"....p...."<<cal->getNextUnit().time<<endl;
	cal->remove();
	cal->show();

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
	Run();

	delete cal;
	cout << "/////////////////////////////////////////////////////////////"<<endl;
	
	return 0;
}
