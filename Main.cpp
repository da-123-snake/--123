#include<thread>
#include "Building.h"
#include"Function.h"
int main() {
	bool ft = true;
	cout << "��ӭʹ�õ���ģ�������ڱ�ģ�����У������Դ���һ��¥��ȷ������ĵ���" << endl;
	cout<<"��Ŀ��¥������Ȼ��������Ҫ�������ݵĳ˿����������ɿ�ʼģ�⡣\n\n������������ѡ����:" << endl;
	while (ft) {
		run(ft);
	}
	return 0;
}
