#include "PetriSim.h"

#include "calendar.h"
int main(int argc,const char* argv[])
{

	SCCalendar* cal = new SCCalendar();
	SCPlace p;
//	CalElement el = new CalElement(p, 2.0);
	cal->insert(p, 2.0);
		cout << "cal->head->cont->time"<<cal->getFirst()->cont->time << endl;
		cout << "cal->head->pre->time"<<cal->getFirst()->pre->time << endl;
		cout << "cal_fisrt->->time"<<cal->getFirst()->time << endl;
		cout << "pocet"<<cal->getCount()<<endl;
	cal->insert(p, 3.0);
		cout << "cal->head->cont->time"<<cal->getFirst()->cont->time << endl;
		cout << "cal->head->pre->time"<<cal->getFirst()->pre->time << endl;
		cout << "cal_fisrt->->time"<<cal->getFirst()->time << endl;
		cout << "pocet"<<cal->getCount()<<endl;
	cal->insert(p, 1.0);
		cout << "cal->head->cont->time"<<cal->getFirst()->cont->time << endl;
		cout << "cal->head->pre->time"<<cal->getFirst()->pre->time << endl;
		cout << "cal_fisrt->->time"<<cal->getFirst()->time << endl;
		cout << "pocet"<<cal->getCount()<<endl;
cout<<"vlozena trojka melo by byt 2, 3";	cal->show();
SCPlace* place;
SCCalendarUnit unit(place,5.0);
cal->insert(unit);
		cout << "cal->head->cont->time"<<cal->getFirst()->cont->time << endl;
		cout << "cal->head->pre->time"<<cal->getFirst()->pre->time << endl;
		cout << "cal_fisrt->->time"<<cal->getFirst()->time << endl;
		cout << "pocet"<<cal->getCount()<<endl;
		cout << "end" << cal->getLast()->time <<endl;
		cal->show();
		cout<<"....p...."<<cal->getNextUnit().time<<endl;
		cal->remove();
		cout<<"show po delete"<<endl;
		cal->show();

//	cal->insert(p[2], 3.4);
/*	SCPlace p[5];
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
	*/
	return 0;
}
