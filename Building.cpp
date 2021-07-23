#include "Building.h"
People::People(int arrive, int ID, int Floor_Num)
{
	ArrivalTime = arrive;
	if_OnElevator = false;
	CurrentFloor =rand() % Floor_Num; 
	Destination =rand() % Floor_Num;  
	if (Floor_Num != -1) {
		while (Destination == CurrentFloor) { //ȷ��Ŀ��¥��͵�ǰ¥�㲻һ��
			Destination = rand() % Floor_Num; 
		}
	}
	Id = ID;
}
int People::getArrivalTime()
{
	return ArrivalTime;
}
int People::getCurrentFloor()
{
	return CurrentFloor;
}
int People::getDestination()
{
	return Destination;
}
int People::getExitTime()
{
	return ExitTime;
}
int People::getWaitTime()
{
	WaitTime = ExitTime - ArrivalTime;
	return WaitTime;
}
int People::getId()
{
	return Id;
}
int People::getDirection()
{
	if (CurrentFloor < Destination) { //���Ϸ���1
		Direction = 1;
		return 1;
	}
	else { //���·���0
		Direction = 0;
		return 0;
	}
}
bool People::get_if_OnElevator()
{
	return if_OnElevator;
}
void People::set_if_OnElevator(bool a)
{
	if_OnElevator = a;
}

void People::setArrivalTime(int AT)
{
	ArrivalTime = AT;
}
void People::setExitTime(int ET)
{
	ExitTime = ET;
}

void People::setCurrentFloor(int CF)
{
	CurrentFloor = CF;
}
void People::setDestination(int Destin)
{
	Destination = Destin;
}
void People::setDirection(int D)
{
	Direction = D;
}
void People::setId(int ID)
{
	Id = ID;
}


Elevator::Elevator()
{
	Elevator_Number = -1;
	Elevator_Current_Floor = 0;//���õ��ݳ�ʼ���ڵ�0��
	vector <People> Elevator_people;
	If_Empty = true;
}
Elevator::Elevator(int ID)
{
	Elevator_Number = ID;
	Elevator_Current_Floor = 0;
	vector <People> Elevator_people;
	If_Empty = true;
}
int Elevator::getElevator_Current_Floor()
{
	return Elevator_Current_Floor;
}
int Elevator::getElevatorNumber()
{
	return Elevator_Number;
}
vector<People> Elevator::getElevator_People()
{
	return Elevator_People;
}
bool Elevator::get_If_Empty()
{
	if (Elevator_People.empty() == false) {
		If_Empty = false;
		return false; 
	}
	else if (Elevator_People.empty() == true) {
		If_Empty = true;
		return true; 
	}
}
void Elevator::set_and_print_Elevator_Current_Floor(int f)
{
	int IDNum = this->Elevator_Number + 1;
	if (f == -1) { 
		return;
	}
	else { 
		cout<<"\n"<<IDNum << " �ŵ��ݴӵ� " << Elevator_Current_Floor;
		Elevator_Current_Floor = f;
		cout << " �㵽�� " << Elevator_Current_Floor << " ��\n";
	}
}
void Elevator::setElevatorNumber(int n)
{
	Elevator_Number = n;
}
void Elevator::set_If_Empty(bool i)
{
	If_Empty = i;
}
bool Elevator::still_exiting()
{
	if (Elevator_People.size() == 0) { //����������û������Ҫ�µ���
		return false;
	}
	for (int i = 0; i < Elevator_People.size(); i++) {
		if (Elevator_People[i].getDestination() == Elevator_Current_Floor) { //����Ҫ�µ���
			return true;
		}
	}
	return false;
}
People Elevator::exit_Elevator_People(int cf)//�µ���
{
	for (int i = 0; i < Elevator_People.size(); i++) {
		if (Elevator_People[i].getDestination() == cf) { //�ҳ���Ҫ�µ��ݵ���
			People l_pepple = Elevator_People[i]; 
			Elevator_People.erase(Elevator_People.begin() + i);
			cout << "  �µ���: �˿� " << l_pepple.getId() << " ����� " << Elevator_Current_Floor << " ��\n";
			return l_pepple;
		}
	}
}
void Elevator::load_Elevator_People(People &passe) //���˷����������
{
	passe.set_if_OnElevator(true); 
	Elevator_People.push_back(passe); 
}

Building::Building(int e_num, int f_num)
{
	elevator_Num = e_num;
	floor_Num = f_num;
	for (int i = 0; i < elevator_Num; i++) { 
		Elevator my_elevator(i); 
		Elevator_vec.push_back(my_elevator); 
	}

	for (int i = 0; i < floor_Num; i++) { 
		vector <People> PeopleQueue;//ʹ�ö��У���֤�����Ƚ�
		Floor_vec.push_back(PeopleQueue); 
	}
}
int Building::get_elevators()
{
	return elevator_Num;
}

int Building::get_floors()
{
	return floor_Num;
}
vector<Elevator> Building::get_ElevatorVec()
{
	return Elevator_vec;
}
void Building::set_elevators(int e)
{
	elevator_Num = e;
}
void Building::set_floors(int f)
{
	floor_Num = f;
}
vector<vector<People>> Building::get_FloorVec()
{
	return Floor_vec;
}
void Building::add_People_Floor(People p)
{
	Floor_vec[p.getCurrentFloor()].push_back(p);
}
void Building::loading_people(int e, int f, int tag)//��������˶�������ͬ���˷������
{
	int k = Floor_vec[f].size(), j = 0;
	for (int i = 0; i < k; i++) {
		if (Elevator_vec[e].getElevator_People().size() >= 20)
			break;
		People p = Floor_vec[f][j];
		if (p.getDirection() == tag) {
			Elevator_vec[e].load_Elevator_People(p);
			Floor_vec[f].erase(Floor_vec[f].begin() + j);
			cout << "  �ϵ���: �˿� " << p.getId() << " �ڵ� " << f << " ���ϵ���\n";
			j--;
		}
		j++;
	}
}
int Building::Function(int count, queue<People>& Exit_P, int max_floor)
{
	int num_exited = 0;//����������
	for (int i = 0; i < Elevator_vec.size(); i++) { 
		int d_floor = -1; //Ŀ��¥��
		int c_floor = Elevator_vec[i].getElevator_Current_Floor(); //����¥��
		if (Floor_vec[0].empty() == false&& Elevator_vec[i].getElevator_People().size()<20)  //�����ǰ¥�����ˣ�ͣ�ڴ˲�
			d_floor = 0;
		else { //����
			if (Elevator_vec[i].get_If_Empty() == false) {//���ݲ�Ϊ��
				d_floor = Elevator_vec[i].getElevator_People().front().getDestination();
				if (d_floor > c_floor) {//��������
					for (int p = 0; p < Elevator_vec[i].getElevator_People().size(); p++) {
						if ((Elevator_vec[i].getElevator_People()[p].getDestination() > c_floor) && (Elevator_vec[i].getElevator_People()[p].getDestination() < d_floor))
							d_floor = Elevator_vec[i].getElevator_People()[p].getDestination();
					}
					int cf = c_floor + 1;
					for (cf; cf < d_floor; cf++) { 
						if (Floor_vec[cf].empty())
							continue;
						else if (Floor_vec[cf].front().getDirection() == 1) { 
							d_floor = Floor_vec[cf].front().getCurrentFloor();
							break;
						}
					}
				}//Ŀ��¥��Ϊ����Ҫȥ�����¥����ߴ�¥��֮����Ҫ���ϵ�������¥��
				else if (d_floor < c_floor) {//��������
					for (int p = 0; p < Elevator_vec[i].getElevator_People().size(); p++) {
						if ((Elevator_vec[i].getElevator_People()[p].getDestination() < c_floor) && (Elevator_vec[i].getElevator_People()[p].getDestination() > d_floor))
							d_floor = Elevator_vec[i].getElevator_People()[p].getDestination();
					}
					int cf = c_floor - 1;
					for (cf; cf > d_floor; cf--) {
						if (Floor_vec[cf].empty())
							continue;
						else if (Floor_vec[cf].front().getDirection() == 0) { 
							d_floor = Floor_vec[cf].front().getCurrentFloor();
							break;
						}
					}
				}//Ŀ��¥��Ϊ����Ҫȥ�����¥����ߴ�¥��֮����Ҫ���µ�������¥��
			}
			else if (Elevator_vec[i].get_If_Empty() == true) {//����������
				for (int k = 0; k < Floor_vec.size(); k++) {
					if (!Floor_vec[k].empty()) { //��Ϊ��
						d_floor = k;
						break;
					}
				}
			}
		}
		int sum = 0;
		Elevator_vec[i].set_and_print_Elevator_Current_Floor(d_floor);
		while (Elevator_vec[i].still_exiting()) { //����Ҫ�µ���
			People l_people = Elevator_vec[i].exit_Elevator_People(Elevator_vec[i].getElevator_Current_Floor());//�µ���
			l_people.setExitTime(count);
			Exit_P.push(l_people); //���˼�������ݵ�ջ����
			num_exited++; //������������1
		}
		if (d_floor >= c_floor ) {
			if (d_floor != -1)
				this->loading_people(i, d_floor , 1);//�����ϵ���
		}
		if (d_floor <= c_floor ) {
			if (d_floor != -1)
				this->loading_people(i, d_floor, 0);//�����ϵ���
		}
		if (d_floor == max_floor || d_floor == 0)
		{
			this->loading_people(i, d_floor, 1);//�����ϵ���
			this->loading_people(i, d_floor, 0);//�����ϵ���
		}
		/*for (int j = 0; j < Elevator_vec[i].getElevator_People().size(); j++)
			sum++;*/
		cout << "��ʱ "<< i + 1 <<" �ŵ����ϵ�����Ϊ��" << Elevator_vec[i].getElevator_People().size() << endl;
	}
	return num_exited;

}

