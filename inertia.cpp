
#include "pch.h"
#include <iostream>

using namespace std;

class answers{				//base class. this class is respsible for all the answers such as centroid, moment of inertia etc.
	
public:
	virtual double Ixx() = 0;				//moment of inertia about x axis
	virtual double Iyy() = 0;				// moment of inertia about y axis
	virtual double Y_centroid() = 0;		// y centroid
	virtual double X_centroid() = 0;		// x centroid
	virtual void set_parameters() = 0;		//setting shape parameters
	void print_answers() {					//the function is responsible  for printing the values
		cout << "Ixx value is: " << Ixx() << endl;	
		cout << "Iyy value is: " << Iyy() << endl;
		cout << "Y coordinate Centroid is (from top): " << Y_centroid() << endl;
		cout << "X coordinate Centroid is (from left): " << X_centroid() << endl;
	}
};

class rectangular:public answers{			//rectangle shape
private:
	double width; double height;			//rectangle parameters
	
public:
	void set_parameters() {					//asks user to input parameters
		cout << "enter rectangle height" << endl;
		cin >> height;
		cout << "enter rectangle width" << endl;
		cin >> width;
	}
		
	double Ixx() {							//moment of inertia about x axis
		return (0.08333333333)*width*height*height*height;
	}

	double Y_centroid() {					//y centroid
		return height / 2;
	}

	double X_centroid() {					//x centroid
		return width / 2;
	}
			
	double Iyy() {							//moment of inertia about y axis
		return (0.08333333333)*height*width*width*width;
	}

	
};

class hollow_rectangular:public answers {			
private:
	double width; double height; double inner_width; double inner_height;
public:
	void set_parameters() {
		cout << "enter rectangle inner width" << endl;
		cin >> inner_width;
		cout << "enter rectangle iner height" << endl;
		cin >> inner_height;
		cout << "enter rectangle height" << endl;
		cin >> height;
		cout << "enter rectangle width" << endl;
		cin >> width;
	}

	double Ixx() {
		return 0.08333333333*((width*height*height*height) - (inner_width*inner_height*inner_height*inner_height));
	}

	double Iyy() {
		return 0.08333333333*((height*width*width*width) - (inner_width*inner_width*inner_width*inner_height));
	}

	double Y_centroid() {
		return height / 2;
	}

	double X_centroid() {
		return width / 2;
	}


};

class circle :public answers{				//all done
private:
	double circle_radius;
	
public:
	void set_parameters() {
		cout << "please set your circle radius.(mm)" << endl;
		cin >> circle_radius;
	}

	double Ixx() {
		return (3.14159*0.25*circle_radius*circle_radius*circle_radius*circle_radius);
	}

	double Iyy() {
		return Ixx();
	}

	double Y_centroid() {
		return circle_radius;
	}

	double X_centroid() {
		return circle_radius;
	}
};

class hollow_circle:public answers{			//all done
private:
	double circle_radius; double hollow_radius;

public:
	void set_parameters() {
		cout << "enter circle radius" << endl;
		cin >> circle_radius;
		cout << "enter hollow radius" << endl;
		cin >> hollow_radius;
	}
	
	double Ixx() {
		return (3.14159*0.25*((circle_radius*circle_radius*circle_radius*circle_radius)-(hollow_radius*hollow_radius*hollow_radius*hollow_radius)));
	}

	double Iyy() {
		return Ixx();
	}

	double Y_centroid() {
		return circle_radius;
	}

	double X_centroid() {
		return circle_radius;
	}
};

class I_beam:public answers {			//all done. If there is symmetry about the y axis, no parallal axis theorem is needed for Iyy.
private:
	double TFw; double TFt; double Wt; double Wh; double BFt;double BFw;
	double centroid_web; double centroid_Bf; double centroid_Tf;
	double TFarea; double BFarea; double web_area; double I_centroid;
public:
	void set_parameters() {
		cout << "I-beam setup" << endl;
		cout << "set the top flange width" << endl;
		cin >> TFw;
		cout << "set the top flange thickness" << endl;
		cin >> TFt;
		cout << "set the web thickness" << endl;
		cin >> Wt;
		cout << "set the web height" << endl;
		cin >> Wh;
		cout << "set bottom flange thickness" << endl;
		cin >> BFt;
		cout << "set bottom flange width" << endl;
		cin >> BFw;
	}

	double Y_centroid() {
		centroid_Tf = TFt / 2;
		centroid_web = TFt + (0.5*Wh);
		centroid_Bf = TFt + Wh + 0.5*(BFt);
		TFarea = (TFw*TFt);
		BFarea = (BFw*BFt);
		web_area = Wh * Wt;
		I_centroid = ((TFarea*centroid_Tf) + (BFarea*centroid_Bf)*(centroid_web*web_area)) / (web_area + TFarea + BFarea);
		return I_centroid;
	}

	double X_centroid() {
		if (TFw > BFw) {
			return TFw / 2;
		}

		if (TFw < BFw) {
			return BFw / 2;
		}

		if (TFw == BFw) {
			return TFw / 2;
		}
	}

	double Ixx() {
		return 0.08333333*((TFw*TFt*TFt*TFt) + (Wt*Wt*Wt*Wh) + (BFw*BFt*BFt*BFt))+
			   TFarea*(I_centroid - centroid_Tf)*(I_centroid - centroid_Tf)+
		       web_area*(I_centroid - centroid_web)*(I_centroid - centroid_web)+
		       BFarea*(I_centroid - centroid_Bf)*(I_centroid - centroid_Bf);
	}

	double Iyy() {
		return 0.08333333*((TFt*TFw*TFw*TFw) + (Wt*Wh*Wh*Wh) + (BFt*BFw*BFw*BFw));
	}

};

class T_beam :public answers {		//t beam
private:
	double TFw; double TFt; double Wh; double Wt;
	double web_area; double flange_area;
	double web_centroid; double flange_centroid; double T_centroid;
public:

	void set_parameters() {
		cout << "T beam setup" << endl;
		cout << "Enter flange width" << endl;
		cin >> TFw;
		cout << "enter flange thickness" << endl;
		cin >> TFt;
		cout << "enter web height" << endl;
		cin >> Wh;
		cout << "enter web thickness" << endl;
		cin >> Wt;
	}

	double Y_centroid() {
		web_area = Wh * Wt;
		flange_area = TFw * TFt;
		web_centroid = TFt + 0.5*Wh;
		flange_centroid = 0.5*TFt;
		T_centroid = ((flange_area*flange_centroid) + (web_area*web_centroid)) / (web_area + flange_area);
		return T_centroid;
	}

	double X_centroid() {
		return TFw / 2;
	}

	double Ixx() {
		return 0.08333333333*((TFw*TFt*TFt*TFt) + (Wt*Wh*Wh*Wh))
			   + web_area * (T_centroid - web_centroid)*(T_centroid - web_centroid)
			   + flange_area * (T_centroid - flange_centroid)*(T_centroid - flange_centroid);
	}

	double Iyy() {
		return 0.08333333333*((TFt*TFw*TFw*TFw) + (Wh*Wt*Wt*Wt));
	}
};

class L_beam :public answers{			//all done
private:
	double BFw; double BFt; double LFh; double LFt;
	double left_centroid_Y; double bottom_centroid_Y; double L_centroid_Y;		//centroid parameters for Y centroid
	double left_centroid_X; double bottom_centroid_X; double L_centroid_X;
	double bottom_area; double left_area;
public:
	void set_parameters() {
		cout << "L - beam setup." << endl;
		cout << "Enter bottom flange width" << endl;
		cin >> BFw;
		cout << "Enter bottom flange thickness" << endl;
		cin >> BFt;
		cout << "Enter left hand flange height" << endl;
		cin >> LFh;
		cout << "Enter left had flange thickness" << endl;
		cin >> LFt;
	}

	double Y_centroid() {
		bottom_area = BFt * BFw;
		left_area = LFh * LFt;
		left_centroid_Y = LFh * 0.5;
		bottom_centroid_Y = LFh + 0.5*BFt;
		L_centroid_Y = ((bottom_area*bottom_centroid_Y) + (left_area*left_centroid_Y)) / (left_area + bottom_area);
		return L_centroid_Y;
	}

	double X_centroid() {
		left_centroid_X = LFt*0.5;
		bottom_centroid_X = BFw*0.5;
		L_centroid_X = ((left_centroid_X*left_area) + (bottom_centroid_X*bottom_area)) / (left_area + bottom_area);
		return L_centroid_X;
	}

	double Ixx() {
		return 0.08333333*((BFw*BFt*BFt*BFt) + (LFt*LFh*LFh*LFh))
			+ left_area * (L_centroid_Y - left_centroid_Y)*(L_centroid_Y - left_centroid_Y)
			+ bottom_area * (L_centroid_Y - bottom_centroid_Y)*(L_centroid_Y - bottom_centroid_Y);
	}

	double Iyy() {
		return 0.08333333*((BFt*BFw*BFw*BFw) + (LFh*LFt*LFt*LFt))
			+ left_area * (L_centroid_X - left_centroid_X)*(L_centroid_X - left_centroid_X)
			+ bottom_area * (L_centroid_X - bottom_centroid_X)*(L_centroid_X- bottom_centroid_X);
	}

};

class channel_beam :public answers {			//Ixx issue. gotta check with L beam as well.
private:
	double h; double Wt; double RFh; double RFt; double LFh; double LFt;
	double right_area; double left_area; double web_area;
	double right_centroid_Y; double left_centroid_Y; double web_centroid_Y; double C_centroid_Y;	//y centroid parameters
	double right_centroid_X; double left_centroid_X; double web_centroid_X; double C_centroid_X;
public:
	void set_parameters() {		
		cout << "channel beam setup" << endl;
		cout << "enter channel width" << endl;
		cin >> h;
		cout << "enter web thickness" << endl;
		cin >> Wt;
		cout << "enter right flange height" << endl; //top
		cin >> RFh;
		cout << "enter right flange thickness" << endl;
		cin >> RFt;
		cout << "enter left flange height" << endl; //bottom
		cin >> LFh;
		cout << "ener left flange width" << endl;
		cin >> LFt;
	}

	double Y_centroid(){
		web_area = (h*Wt);
		right_area = RFt * RFh;
		left_area = LFh * LFt;
		web_centroid_Y = Wt * 0.5;
		right_centroid_Y =( 0.5*RFh) + Wt;
		left_centroid_Y = (0.5*LFh) + Wt;
		C_centroid_Y = ((web_area*web_centroid_Y) + (right_area*right_centroid_Y) + (left_area*left_centroid_Y)) / (right_area + left_area + web_area);
		return C_centroid_Y;
	}
	
	double X_centroid() {
		web_centroid_X = 0.5*h;
		left_centroid_X = LFt / 2;
		right_centroid_X = h - (RFt / 2);
		C_centroid_X = ((web_area*web_centroid_X) + (left_centroid_X*left_area) + (right_centroid_X*right_area)) / (right_area + left_area + web_area);
		return C_centroid_X;
	}

	double Ixx() {	
		return 0.08333333*((h*Wt*Wt*Wt) + (RFh*RFh*RFh*RFt) + (LFh*LFh*LFh*LFt)) +
			right_area * (C_centroid_Y - right_centroid_Y)*(C_centroid_Y - right_centroid_Y)
			+ left_area * (C_centroid_Y - left_centroid_Y)*(C_centroid_Y - left_centroid_Y)
			+ web_area * (C_centroid_Y - web_centroid_Y)*(C_centroid_Y - web_centroid_Y);
	}

	double Iyy() {
		return 0.08333333*((h*h*h*Wt) + (RFh*RFt*RFt*RFt) + (LFh*LFt*LFt*LFt)) +
			right_area * (C_centroid_X - right_centroid_X)*(C_centroid_X - right_centroid_X)
			+ left_area * (C_centroid_X - left_centroid_X)*(C_centroid_X - left_centroid_X)
			+ web_area * (C_centroid_X - web_centroid_X)*(C_centroid_X - web_centroid_X);
	}
};

class triangular:public answers {		//symmetric about y
	double b; double h;
	void set_parameters() {
		cout << "triangular shape. please note that it is symmetric about y axis." << endl;
		cout << "insert triangle height" << endl;
		cin >> h;
		cout << "insert triangualr width" << endl;
		cin >> b;
	}

	double Y_centroid() {
		return 0.666666666*h;
	}

	double X_centroid() {
		return b / 2;
	}

	double Ixx() {
		return (0.5*b*h*h*h / 18);
	}

	double Iyy() {
		return (h*b*b*b*0.5*0.5*0.5 / 6);
	}
};

int chooseShape() {
	int x; char choose;
	answers* d;																		//initialize base class instance
	rectangular a; hollow_rectangular b; circle c; hollow_circle z; I_beam e;		//class instances
	T_beam f; L_beam g; channel_beam h; triangular i;								//class instances
		cout << "        " << endl;
		cout << "welcome to the moment of inertia calculator." << endl;
		cout << "See the list below, and enter the desired key for the shape you need." << endl;
		cout << "a - rectangular ; b - hollow rectangular ; c - circle ; d - hollow circle" << endl;
		cout << "e - I beam ; f - T beam ; g - L beam ; h - channel beam ; i - triangular" << endl;
		cin >> choose;
		if (choose == 'a') {
			d = &a;						//sets base class poniter to the address of rectangle
			d->set_parameters();		//calling set parameters function for rectangle
			d->Y_centroid();			//calling y centroid function for rectangle
			d->X_centroid();			//calling x centroid function for rectangle
			d->Ixx();					// calling moment of inertia about x for rectangle
			d->Iyy();					//calling moment of inertia about y for rectangle
			d->print_answers();			//print the function answers.
		}
		if (choose == 'b') {			//similarly, but for hollow rectangle.
			d = &b;
			d->set_parameters();
			d->Y_centroid();
			d->X_centroid();
			d->Ixx();
			d->Iyy();
			d->print_answers();
		}
		
		if (choose == 'c') {		//circle
			d = &c;
			d->set_parameters();
			d->Y_centroid();
			d->X_centroid();
			d->Ixx();
			d->Iyy();
			d->print_answers();
		}
		
		if (choose == 'd') {		//hollow circle
			d = &z;
			d->set_parameters();
			d->Y_centroid();
			d->X_centroid();
			d->Ixx();
			d->Iyy();
			d->print_answers();
		}
		
		if (choose == 'e') {		//I beam
			d = &e;
			d->set_parameters();
			d->Y_centroid();
			d->X_centroid();
			d->Ixx();
			d->Iyy();
			d->print_answers();
		}
		
		if (choose == 'f') {		//t beam
			d = &f;
			d->set_parameters();
			d->Y_centroid();
			d->X_centroid();
			d->Ixx();
			d->Iyy();
			d->print_answers();
		}
		
		if (choose == 'g') {		// l beam
			d = &g;
			d->set_parameters();
			d->Y_centroid();
			d->X_centroid();
			d->Ixx();
			d->Iyy();
			d->print_answers();
		}
		
		if (choose == 'h') {		//channel beam
			d = &h;
			d->set_parameters();
			d->Y_centroid();
			d->X_centroid();
			d->Ixx();
			d->Iyy();
			d->print_answers();
		}
		
		if (choose == 'i') {		//triangular
			d = &i;
			d->set_parameters();
			d->Y_centroid();
			d->X_centroid();
			d->Ixx();
			d->Iyy();
			d->print_answers();
		}
		
		cout << "enter 5 to exit, else enter any other number to continue." << endl;
		cin >> x;
		if (x != 5) {
			chooseShape();		//call the function again if the user intends to use it (recursion)
		}
		else return 0;			//else quit
	
}

			


int main() {
	chooseShape();
	system("pause");
}
