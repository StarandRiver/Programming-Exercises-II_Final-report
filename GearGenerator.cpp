#include<iostream>
#include<string>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<list>
#define GNUPLOT_PATH "C:/PROGRA~1/gnuplot/bin/gnuplot.exe"		//GNUプロットのパス(使用者が各自で指定)
FILE* gp;	//GNUプロットを操作するための変数の定義

using namespace std;

//vector<float> gearXY;
list<float> gearXY;

class gear_param
{
public:
	float m;
	float d;
	int z;
	float da; // 歯先円直径
	float df; // 歯底円直径
	float db; // 基礎円直径
	float zd; // 歯間の角度(プロット時に使用)
	float m_tmp;
	float d_tmp;
	int z_tmp;

	void input(int& A) //入力用関数
	{ // 入力用関数
		string m_tmp;

		cout << "モジュールmの値を入力してください" << endl;
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
			cout << "正の実数を入力してください" << endl;
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
			cout << "ピッチ円直径dの値を入力してください" << endl;
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
				cout << "正の実数を入力してください" << endl;
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
			cout << "歯数zの値を入力してください" << endl;
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
				cout << "正の実数を入力してください" << endl;
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
	void calcpram() //パラメータ計算用関数
	{ // パラメータ計算用関数
		da = d + 2 * m;
		df = d - 2.5 * m;
		db = d * cos(20 * 3.1415 / 180);
	}
	void printpram()    //パラメータ出力用関数
	{
		cout << "=====パラメータ=====" << endl;
		cout << "モジュールm:" << m << endl;
		cout << "歯数z:" << z << endl;
		cout << "圧力角α:20°" << endl;
		cout << "ピッチ円直径d:" << d << endl;
		cout << "歯先円直径da:" << da << endl;
		cout << "歯底円直径df:" << df << endl;
		cout << "基礎円直径db:" << db << endl;
		cout << "====================" << endl;
	}
};

void drawCircle(float& d)   //入力形式:書きたい円の直径
{
	fprintf(gp, "set parametric\n");
	fprintf(gp, "replot [0:2*pi] %f*cos(t),%f*sin(t)\n", d / 2, d / 2); // 基礎円直径の描写
}

void calcinvolute(int& z, float& db, float& da, float& df) //入力形式:歯数,基礎円直径, 歯先円直径,歯底円直径
{
	float theta_B = (3.1415 / z) + 2 * (tan(20 * 3.1415 / 180) - (20 * 3.1415 / 180));
	for (float t = 0; t < 360;)
	{
		double ra = da / 2;
		for (float i = 0; i < 50; i = i + (df / da)) // インボリュート曲線のプロット
		{
			double omega = t * 3.1415 / 180.0;
			double phi = i * 3.1415 / 180.0;
			double theta = phi - atan(phi);
			double x_tmp = (db / 2) * sqrt(1 + phi * phi) * cos(phi - atan(phi));
			double y_tmp = (db / 2) * sqrt(1 + phi * phi) * sin(phi - atan(phi));
			double x = x_tmp * cos(omega) - y_tmp * sin(omega);
			double y = x_tmp * sin(omega) + y_tmp * cos(omega);
			double lxy = sqrt(x_tmp * x_tmp + y_tmp * y_tmp); // 歯先円からプロットが飛び出していないかの判定
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
			double lxy = sqrt(x_tmp * x_tmp + y_tmp * y_tmp); // 歯先円からプロットが飛び出していないかの判定
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
		outfile << *i << " ";    //x座標の読み出し
		++i;
		outfile << *i << endl;   //y座標の読み出し
	}
	outfile.close();
	fprintf(gp, "set output 'gear.eps'\n");
	fprintf(gp, "plot 'gear.dat' with lines\n");
}

void Enterdraw()
{              // グラフ読み込み関数(参考:香川大学,C言語でgnuplotを動かす,https://www.eng.kagawa-u.ac.jp/~haruna/memo/gnuplot/gnuC.html)
	fflush(gp); // バッファに格納されているデータを吐き出す（必須）
	system("pause");
	fprintf(gp, "unset key\n");
	fprintf(gp, "exit\n"); // gnuplotの終了
	_pclose(gp);
	fprintf(gp, "set terminal postscript dxf\n");
}

int main() {
	//ローカル変数の定義
	string tmp_mode;
	int mode = 0;

		//入力モード選択部
		cout << "モジュールmとピッチ円直径dから歯車を作成：1 " << endl;
		cout << "モジュールmと歯数zから歯車を作成：2" << endl;
		cin >> tmp_mode;
		try
		{
			mode = stoi(tmp_mode);
		}
		catch (invalid_argument& e)
		{
			cerr << e.what() << endl;
		}
		while (1) {	//入力条件に適合するものが入力されるまで繰り返し
			if (mode == 1 || mode == 2)
			{
				break;
			}
			cout << "1か2の値を入力してください" << endl;
			cin >> tmp_mode;
			try { mode = stoi(tmp_mode); }
			catch (invalid_argument& e) { cerr << e.what() << endl; }
		}

		gear_param gear_1;

		gear_1.input(mode);	//ユーザー設定パラメータの入力

		gear_1.calcpram();	//各種パラメータの計算

		//計算されたパラメータの表示
		gear_1.printpram();

		if ((gp = _popen(GNUPLOT_PATH, "w")) == NULL) {	// gnuplotをパイプで起動
			fprintf(stderr, "ファイルが見つかりません %s.", GNUPLOT_PATH);
			exit(EXIT_FAILURE);
		}
		string filename = "gear1";
		calcinvolute(gear_1.z, gear_1.db, gear_1.da, gear_1.df);
		outputdatfile();
		//drawCircle(gear_1.db);	//基礎円を書くときにはコメントを外す

		Enterdraw();
}
