#include"Function.h"
void getParameter(int& e_num, int& f_num, int& p_num)
{
	cout << "_________________________________________________________\n\n���ڿ�ʼģ�⣺" << endl;
	cout << "�����������: ";
	cin >> e_num;
	cout << "������¥����: ";
	cin >> f_num;
	while (f_num <= 1) { 
		cout << "���������������㡣\n";
		cin >> f_num;
	}
	cout << "������˿�����: ";
	cin >> p_num;
	while (p_num <= 0) {
		cout << "������������һ���ˡ�\n";
		cin >> p_num;
	}
	cout << "\n**********************************************************\n����ģ����... \n";
}
void PrintPeople(vector<vector<People>> the_floors, int &max_floor)
{
	for (int k = 0; k < the_floors.size(); k++) { 
		while (the_floors[k].empty() == false) {
			cout << "  �˿� " << the_floors[k].back().getId() << ": \t����¥�� " << the_floors[k].back().getCurrentFloor() << " \tĿ��¥�㣺" << the_floors[k].back().getDestination() << endl;
			if (max_floor < the_floors[k].back().getCurrentFloor())
				max_floor = the_floors[k].back().getCurrentFloor();
			the_floors[k].pop_back();
		}
	}
}
void run(bool& f)
{
	cout << "1.��ʼģ��\n" << "2.�˳�" << endl;
	srand(time(0));
	int choice;
	cin >> choice;
	//��ʼģ��
	if (choice == 1) {
		int e_num = -1; //������
		int f_num = -1; //����
		int p_num; //����
		int max_floor = 1;//��߲���
		getParameter(e_num, f_num, p_num);
		Building My_Building(e_num, f_num); //��¥
		int count = 1; //����
		int People_ID = 0; //�˵ı��
		int num_exited = 0; //�����ݵ�����
		queue <People> Exit_People; //�����ݵ��˵Ķ���
		for (int i = 0; i < p_num; i++) {  //��ʼ��
			People the_People(count, People_ID, f_num); 
			People_ID++; 
			My_Building.add_People_Floor(the_People);
		}
		PrintPeople(My_Building.get_FloorVec(), max_floor);
		//cout << "***" << max_floor << " ** " << endl;
		while (num_exited < p_num) {
			cout << "\n���������������������� " << count << " �Ρ���������������������\n\n";
			num_exited += My_Building.Function(count, Exit_People, max_floor);
			count++;
		}
		cout << "\nģ�����\n******************************************************\n\n������: " << p_num << endl;
		double sum = 0;
		while (!Exit_People.empty()) {
			People current = Exit_People.front();
			sum += current.getWaitTime();
			Exit_People.pop();
		}
		cout << "ƽ���ȴ�ʱ��: " << sum / p_num << "\n__________________________________________________________";
		cout << endl << endl;
	}
	else if (choice == 2) { //����
		f = false;
	}
}