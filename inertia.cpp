//Author:Der Zhi Jeremy Sow
//Date: 20/11/18

#include "pch.h"
#include <iostream>

using namespace std;

class answers{
	
public:
	virtual double Ixx() = 0;				
	virtual double centroid() = 0;
	virtual double Iyy() = 0;
	virtual void set_parameters() = 0;
	void print_answers() {
		cout << "Ixx value is: " << Ixx() << endl;
		cout << "Iyy value is: " << Iyy() << endl;
		cout << "Centroid is (from top): " << centroid() << endl;
	}
};

class rectangular:public answers{
private:
	double width; double height; 
	
public:
	void set_parameters() {
		cout << "enter rectangle height" << endl;
		cin >> height;
		cout << "enter rectangle width" << endl;
		cin >> width;
	}

	double Ixx() {
		return (0.08333333333)*width*height*height*height;
	}

	double centroid() {
		return height / 2;
	}

	double Iyy() {
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
		0.08333333333*((height*width*width*width) - (inner_width*inner_width*inner_width*inner_height));
	}

	double centroid() {
		return height / 2;
	}


};

class circle :public answers{
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

	double centroid() {
		return circle_radius;
	}
};

class hollow_circle:public answers{
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

	double centroid() {
		return circle_radius;
	}
};

class I_beam:public answers {
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

	double centroid() {
		centroid_Tf = TFt / 2;
		centroid_web = TFt + (0.5*Wh);
		centroid_Bf = TFt + Wh + 0.5*(BFt);
		TFarea = (TFw*TFt);
		BFarea = (BFw*BFt);
		web_area = Wh * Wt;
		I_centroid = ((TFarea*centroid_Tf) + (BFarea*centroid_Bf)*(centroid_web*web_area)) / (web_area + TFarea + BFarea);
		return I_centroid;
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

class T_beam :public answers {
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

	double centroid() {
		web_area = Wh * Wt;
		flange_area = TFw * TFt;
		web_centroid = TFt + 0.5*Wh;
		flange_centroid = 0.5*TFt;
		T_centroid = ((flange_area*flange_centroid) + (web_area*web_centroid)) / (web_area + flange_area);
		return T_centroid;
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

class L_beam :public answers{
private:
	double BFw; double BFt; double LFh; double LFt;
	double left_centroid; double bottom_centroid; double L_centroid;
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

	double centroid() {
		bottom_area = BFt * BFw;
		left_area = LFh * LFt;
		left_centroid = LFh * 0.5;
		bottom_centroid = LFh + 0.5*BFt;
		L_centroid = ((bottom_area*bottom_centroid) + (left_area*left_centroid)) / (left_area + bottom_area);
		return L_centroid;
	}

	double Ixx() {
		return 0.08333333*((BFw*BFt*BFt*BFt) + (LFt*LFh*LFh*LFh))
			+ left_area * (L_centroid - left_centroid)*(L_centroid - left_centroid)
			+ bottom_area * (L_centroid - bottom_centroid)*(L_centroid - bottom_centroid);
	}

};

class channel_beam :public answers {
private:
	double h; double Wt; double RFh; double RFt; double LFh; double LFt;
	double right_area; double left_area; double web_area;
	double right_centroid; double left_centroid; double web_centroid; double C_centroid;
public:
	void set_parameters() {
		cout << "channel beam setup" << endl;
		cout << "enter channel width" << endl;
		cin >> h;
		cout << "enter web thickness" << endl;
		cin >> Wt;
		cout << "enter right flange height" << endl;
		cin >> RFh;
		cout << "enter right flange thickness" << endl;
		cin >> RFt;
		cout << "enter left flange height" << endl;
		cin >> LFh;
		cout << "ener left flange width" << endl;
		cin >> LFt;
	}

	double centroid(){
		web_area = (h*Wt);
		right_area = RFt * RFh;
		left_area = LFh * LFh;
		web_centroid = Wt * 0.5;
		right_centroid = 0.5*RFh + Wt;
		left_centroid = 0.5*LFh + Wt;
		C_centroid = ((web_area*web_centroid) + (right_area*right_centroid) + (left_area*left_centroid)) / (right_area + left_area + web_centroid);
		return C_centroid;
	}

	double Ixx() {	
		return 0.08333333*((h*Wt*Wt*Wt) + (RFh*RFh*RFh*RFt) + (LFh*LFh*LFh*LFt)) +
			right_area * (C_centroid - right_centroid)*(C_centroid - right_centroid)
			+ left_area * (C_centroid - left_centroid)*(C_centroid - left_centroid)
			+ web_area * (C_centroid - web_centroid)*(C_centroid - web_centroid);
	}

	double Iyy() {

	}


};


			


int main() {
	answers* d;		//base 
	circle b;	//
	d = &b;
	d->set_parameters();
	d->centroid();
	d->Ixx();
	d->Iyy();
	d->print_answers();



	
	
	system("pause");
}
