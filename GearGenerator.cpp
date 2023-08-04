#include<iostream>
#include<string>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<list>
#define GNUPLOT_PATH "C:/PROGRA~1/gnuplot/bin/gnuplot.exe"		//GNU�v���b�g�̃p�X(�g�p�҂��e���Ŏw��)
FILE* gp;	//GNU�v���b�g�𑀍삷�邽�߂̕ϐ��̒�`

using namespace std;

//vector<float> gearXY;
list<float> gearXY;

class gear_param
{
public:
	float m;
	float d;
	int z;
	float da; // ����~���a
	float df; // ����~���a
	float db; // ��b�~���a
	float zd; // ���Ԃ̊p�x(�v���b�g���Ɏg�p)
	float m_tmp;
	float d_tmp;
	int z_tmp;

	void input(int& A) //���͗p�֐�
	{ // ���͗p�֐�
		string m_tmp;

		cout << "���W���[��m�̒l����͂��Ă�������" << endl;
		cin >> m_tmp;
		try
		{
			m = stof(m_tmp);
		}
		catch (invalid_argument& e)
		{
			cerr << e.what() << endl;
		}
		while (1)
		{
			if (m > 0)
			{
				break;
			}
			cout << "���̎�������͂��Ă�������" << endl;
			cin >> m_tmp;
			try
			{
				m = stof(m_tmp);
			}
			catch (invalid_argument& e)
			{
				cerr << e.what() << endl;
			}
		}
		if (A == 1)
		{
			string d_tmp;
			cout << "�s�b�`�~���ad�̒l����͂��Ă�������" << endl;
			cin >> d_tmp;
			try
			{
				d = stof(d_tmp);
			}
			catch (invalid_argument& e)
			{
				cerr << e.what() << endl;
			}
			while (1)
			{
				if (d > 0)
				{
					break;
				}
				cout << "���̎�������͂��Ă�������" << endl;
				cin >> d_tmp;
				try
				{
					d = stof(d_tmp);
				}
				catch (invalid_argument& e)
				{
					cerr << e.what() << endl;
				}
			}
			z = d / m;
		}
		else if (A == 2)
		{
			string z_tmp;
			cout << "����z�̒l����͂��Ă�������" << endl;
			cin >> z_tmp;
			try
			{
				z = stof(z_tmp);
			}
			catch (invalid_argument& e)
			{
				cerr << e.what() << endl;
			}
			while (1)
			{
				if (z > 0)
				{
					break;
				}
				cout << "���̎�������͂��Ă�������" << endl;
				cin >> z_tmp;
				try
				{
					z = stof(z_tmp);
				}
				catch (invalid_argument& e)
				{
					cerr << e.what() << endl;
				}
			}
			d = m * z;
		}
	}
	void calcpram() //�p�����[�^�v�Z�p�֐�
	{ // �p�����[�^�v�Z�p�֐�
		da = d + 2 * m;
		df = d - 2.5 * m;
		db = d * cos(20 * 3.1415 / 180);
	}
	void printpram()    //�p�����[�^�o�͗p�֐�
	{
		cout << "=====�p�����[�^=====" << endl;
		cout << "���W���[��m:" << m << endl;
		cout << "����z:" << z << endl;
		cout << "���͊p��:20��" << endl;
		cout << "�s�b�`�~���ad:" << d << endl;
		cout << "����~���ada:" << da << endl;
		cout << "����~���adf:" << df << endl;
		cout << "��b�~���adb:" << db << endl;
		cout << "====================" << endl;
	}
};

void drawCircle(float& d)   //���͌`��:���������~�̒��a
{
	fprintf(gp, "set parametric\n");
	fprintf(gp, "replot [0:2*pi] %f*cos(t),%f*sin(t)\n", d / 2, d / 2); // ��b�~���a�̕`��
}

void calcinvolute(int& z, float& db, float& da, float& df) //���͌`��:����,��b�~���a, ����~���a,����~���a
{
	float theta_B = (3.1415 / z) + 2 * (tan(20 * 3.1415 / 180) - (20 * 3.1415 / 180));
	for (float t = 0; t < 360;)
	{
		double ra = da / 2;
		for (float i = 0; i < 50; i = i + (df / da)) // �C���{�����[�g�Ȑ��̃v���b�g
		{
			double omega = t * 3.1415 / 180.0;
			double phi = i * 3.1415 / 180.0;
			double theta = phi - atan(phi);
			double x_tmp = (db / 2) * sqrt(1 + phi * phi) * cos(phi - atan(phi));
			double y_tmp = (db / 2) * sqrt(1 + phi * phi) * sin(phi - atan(phi));
			double x = x_tmp * cos(omega) - y_tmp * sin(omega);
			double y = x_tmp * sin(omega) + y_tmp * cos(omega);
			double lxy = sqrt(x_tmp * x_tmp + y_tmp * y_tmp); // ����~����v���b�g����яo���Ă��Ȃ����̔���
			if (lxy > ra)
			{
				break;
			}
			gearXY.push_back(x);
			gearXY.push_back(y);
		}
		for (float i = 50; i > 0; i = i - (df / da))
		{
			double omega = t * 3.1415 / 180.0 + theta_B;
			double phi = i * 3.1415 / 180.0;
			double theta = phi - atan(phi);
			double x_tmp = (db / 2) * sqrt(1 + phi * phi) * cos(phi - atan(phi));
			double y_tmp = -((db / 2) * sqrt(1 + phi * phi) * sin(phi - atan(phi)));
			double x = x_tmp * cos(omega) - y_tmp * sin(omega);
			double y = x_tmp * sin(omega) + y_tmp * cos(omega);
			double lxy = sqrt(x_tmp * x_tmp + y_tmp * y_tmp); // ����~����v���b�g����яo���Ă��Ȃ����̔���
			if (lxy > ra)
			{
			} // break; }
			else
			{
				gearXY.push_back(x);
				gearXY.push_back(y);
			}
		}

		t = t + (360. / z);
	}
	auto j = gearXY.begin();
	gearXY.push_back(*j);
	++j;
	gearXY.push_back(*j);
	//
	//fprintf(gp, "set output 'gear.dxf'\n");
	//fprintf(gp, "replot 'gear.dat' with lines\n");
}

void outputdatfile()
{
	ofstream outfile("gear.dat", ios_base::out);
	for (auto i = gearXY.begin(); i != gearXY.end(); ++i) {
		outfile << *i << " ";    //x���W�̓ǂݏo��
		++i;
		outfile << *i << endl;   //y���W�̓ǂݏo��
	}
	outfile.close();
	fprintf(gp, "set output 'gear.eps'\n");
	fprintf(gp, "plot 'gear.dat' with lines\n");
}

void Enterdraw()
{              // �O���t�ǂݍ��݊֐�(�Q�l:�����w,C�����gnuplot�𓮂���,https://www.eng.kagawa-u.ac.jp/~haruna/memo/gnuplot/gnuC.html)
	fflush(gp); // �o�b�t�@�Ɋi�[����Ă���f�[�^��f���o���i�K�{�j
	system("pause");
	fprintf(gp, "unset key\n");
	fprintf(gp, "exit\n"); // gnuplot�̏I��
	_pclose(gp);
	fprintf(gp, "set terminal postscript dxf\n");
}

int main() {
	//���[�J���ϐ��̒�`
	string tmp_mode;
	int mode = 0;

		//���̓��[�h�I��
		cout << "���W���[��m�ƃs�b�`�~���ad���玕�Ԃ��쐬�F1 " << endl;
		cout << "���W���[��m�Ǝ���z���玕�Ԃ��쐬�F2" << endl;
		cin >> tmp_mode;
		try
		{
			mode = stoi(tmp_mode);
		}
		catch (invalid_argument& e)
		{
			cerr << e.what() << endl;
		}
		while (1) {	//���͏����ɓK��������̂����͂����܂ŌJ��Ԃ�
			if (mode == 1 || mode == 2)
			{
				break;
			}
			cout << "1��2�̒l����͂��Ă�������" << endl;
			cin >> tmp_mode;
			try { mode = stoi(tmp_mode); }
			catch (invalid_argument& e) { cerr << e.what() << endl; }
		}

		gear_param gear_1;

		gear_1.input(mode);	//���[�U�[�ݒ�p�����[�^�̓���

		gear_1.calcpram();	//�e��p�����[�^�̌v�Z

		//�v�Z���ꂽ�p�����[�^�̕\��
		gear_1.printpram();

		if ((gp = _popen(GNUPLOT_PATH, "w")) == NULL) {	// gnuplot���p�C�v�ŋN��
			fprintf(stderr, "�t�@�C����������܂��� %s.", GNUPLOT_PATH);
			exit(EXIT_FAILURE);
		}
		string filename = "gear1";
		calcinvolute(gear_1.z, gear_1.db, gear_1.da, gear_1.df);
		outputdatfile();
		//drawCircle(gear_1.db);	//��b�~�������Ƃ��ɂ̓R�����g���O��

		Enterdraw();
}
