#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
class People {
private:
	int ArrivalTime, CurrentFloor, Destination, ExitTime, WaitTime, Direction, Id;
	bool if_OnElevator;//�Ƿ��ڵ�����

public:
	People(int arrive = -1, int ID = -1, int numFloor = -1);
	int getArrivalTime();
	int getCurrentFloor();
	int getDestination();
	int getExitTime();
	int getWaitTime();
	int getId();
	int getDirection();//���Ϸ���1�����·���0
	bool get_if_OnElevator();
	void set_if_OnElevator(bool a); 
	void setArrivalTime(int AT);
	void setExitTime(int ET);
	void setCurrentFloor(int CF);
	void setDestination(int Destin);
	void setDirection(int D);//������Ϊ1��������Ϊ0
	void setId(int ID);
};

class Elevator {
private:
	vector <People> Elevator_People; // ���ڴ洢�����������
	int Elevator_Current_Floor;		// ��������¥��
	int Elevator_Number;	// ���ݺ�
	bool If_Empty;//�жϵ����Ƿ�Ϊ�գ���Ϊtrue,����Ϊfalse
public:
	Elevator(); 
	Elevator(int ID); 
	bool get_If_Empty();
	void set_and_print_Elevator_Current_Floor(int f);
	void setElevatorNumber(int n);
	void set_If_Empty(bool i);
	vector <People> getElevator_People();
	int getElevator_Current_Floor();
	int getElevatorNumber();
	bool still_exiting(); //����Ƿ�����Ҫ�µ���
	void load_Elevator_People(People &p); //���˷����������
	People exit_Elevator_People(int cf); // �µ���
};

class Building
{
private:
	int elevator_Num, floor_Num;
	vector<Elevator> Elevator_vec; //�������������ڴ洢����
	vector<vector<People>> Floor_vec; //¥�����������ڴ洢¥�㣬�Լ���¥�����
public:
	Building(int e_num, int f_num);
	int get_elevators();
	int get_floors();
	vector <Elevator> get_ElevatorVec();
	vector<vector<People>> get_FloorVec();
	void set_elevators(int e);
	void set_floors(int f);
	void add_People_Floor(People p); //���˼ӵ�¥��������
	void loading_people(int e, int f, int tag); //��f¥������ϵ���
	int Function(int count, queue<People>& Exitors, int max_floor);
};