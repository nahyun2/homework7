/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("------------------[2023041039]    [�ֳ���]-----------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); 
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); 
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 0;
}

//headnode �ʱ�ȭ�ϴ� �Լ�
headNode* initialize(headNode* h) {

	/* headNode�� NULL�� �ƴϸ�, freeList�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

//����Ʈ �޸� �����ϴ� �Լ�
int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first; 

	listNode* prev = NULL; //���� ��带 ����ų ����ü ������ prev ����
	while(p != NULL) { //p�� NULL�� �� ������ ���� �Ҵ��� ����
		prev = p; 
		p = p->link; 
		free(prev);
	}
	free(h); //��嵵 ���� �Ҵ��� �������ش�.
	return 0;
}



/*
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode ����ü ũ�⸸ŭ�� ���� �Ҵ�
	node->key = key; //�Է¹��� key���� ����� key�� ����

	node->link = h->first; //����� link�� ��尡 ����Ű�� ��带 ����Ŵ
	h->first = node; //��尡 ���� ������ ��带 ����Ű���� ��

	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key)
{	//��� �����κ�
	listNode* node = (listNode*)malloc(sizeof(listNode)); //����Ʈ��� ����ü ũ�⸸ŭ ���� �Ҵ�
	node->key = key; //�Է¹��� key���� ����� key�� ����
	node->link = NULL; //����� link�� NULL�� �ʱ�ȭ

	if(h->first == NULL) // ��尡 �ƹ��͵� ����Ű�� �ʴ´ٸ� == ����Ʈ�� ����ִٸ�
	{
		h->first = node; // ���� ���� ������ ��带 ����Ŵ
		return 0;
	}
	// ����Ʈ�� ������� �ʴٸ�
	listNode* p = NULL; //����Ʈ�� �˻��� ����ü������ p����
	listNode* tail = NULL; // �׻� p���� �� ��� �ڿ����� ����ü ������ tail ����
	// �ʱ⿡ p�� tail�� ���� ���� ��带 ����Ŵ
	p = h->first; 
	tail = h->first;

	while(p != NULL) //p�� NULL�� ������ �ݺ�
	{
		if(p->key >= key) // ���� �Է¹��� key ���� p�� ����Ű�� key������ �۴ٸ�
		{
			if(p == h->first) // ����Ʈ�� ��尡 �Ѱ� ���� ���
			{
				// ����Ʈ�� ó���κп� ��带 ��ġ��Ŵ
				h->first = node; 
				node->link = p;
			}
			else // ����Ʈ�� ��尡 ������ ���� ���
			{
				node->link = p; // �� ���� p�� ����Ŵ
				tail->link = node; //p�� ���� ���� �� ��带 ����Ŵ
			}
			return 0;
		}
		tail = p; // tail�� p�� ��ġ�� �̵�
		p = p->link; // p�� ���� ����� ��ġ�� �̵�
	}
	//�Է¹��� key������ ū ���� ��尡 ���� ���
	tail->link = node; // ����Ʈ�� ���� ������ ��尡 �� ��带 ����Ŵ 
	
	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key)
{
	listNode* node = (listNode*)malloc(sizeof(listNode)); //����Ʈ��� ����ü ũ�⸸ŭ ���� �Ҵ�
	node->key = key; //�Է¹��� key���� ����� key�� ����
	node->link = NULL; //����� link�� NULL�� �ʱ�ȭ

	if(h->first == NULL) // ����Ʈ�� ������� ���
	{
		h->first = node; // ��尡 ���� ������ ��带 ����Ű���� ��
		return 0;
	}
	
	listNode* p = NULL; //����ü������ p�� �����ϰ� NULL�� �ʱ�ȭ
	p = h->first; //p�� ����Ʈ�� ù��° ��带 ����Ű���� ��

	while(p->link != NULL) //p�� link�� NULL�� �� ������ �ݺ�, ����Ʈ�� ������ ��忡 �����ϰ� ��
	{
		p = p->link; 
	}
	
	p->link = node; //p�� link�� ���� ������ ��带 ����Ű���� ��

	return 0;
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) 
{

	if(h->first == NULL) // ��尡 ����Ű�� ��尡 ��������� ����Ʈ�� �������
	{
		printf("������ ����Ʈ�� �����ϴ�.\n");
		return 0;
	}
	
	
	listNode* p = NULL; //����Ʈ��� ����ü������ p�� �����ϰ� NULL�� �ʱ�ȭ

	p = h->first; //p�� ����Ʈ�� ù��° ��带 ����Ű���� �� 
	h->first = p->link;	//��尡 NULL�� ����Ű���� ��
	free(p); //p�� ����Ű�� ��带 ���� �Ҵ� ����

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	if(h->first == NULL) //��尡 ����Ű�� ��尡 ��������� ����Ʈ�� �������
	{
		printf("������ ����Ʈ�� �����ϴ�.\n");
		return 0;
	}

	listNode* p = NULL; //����Ʈ��� ����ü������ p�� �����ϰ� NULL�� �ʱ�ȭ
	listNode* tail = NULL; //����Ʈ��� ����ü������ tail�� �����ϰ� NULL�� �ʱ�ȭ
	p = h->first; //p�� ����Ʈ�� ù��° ��带 ����Ű���� ��
	tail = h->first; //tail�� ����Ʈ�� ù��° ��带 ����Ű���� ��

	while(p != NULL) //p�� NULL�� �ƴϸ� �ݺ�, ����Ʈ�� ������ �ݺ���
	{
		if(p->key == key) //p�� ����Ű�� ����� key���� �Է¹��� key���� ���ٸ�
		{
			if(p == h->first) //p�� ����Ʈ�� ù��° ��带 ����Ű�� �ִٸ�
			{
				h->first = p->link; //��尡 p�� ���� ��带 ����Ű���� ��
				free(p); //p�� ����Ű�� ��带 ���� �Ҵ� ����
				return 0;
			}
			
			tail->link = p->link; //tail�� p�� ���� ��带 ����Ű���� ��
			free(p); //p�� ����Ű�� ��带 ���� �Ҵ� ����
			return 0;
		}
		
		tail = p; //tail�� p�� ��ġ�� �̵�
		p = p->link; //p�� ���� ����� ��ġ�� �̵�

	}

	printf("cannot find node for key.\n"); //�Է¹��� key���� ���� ��带 ã�� ������ ���
	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	if(h->first == NULL) //��尡 ����Ű�� ��尡 ��������� ����Ʈ�� �������
	{
		printf("������ ����Ʈ�� �����ϴ�.\n");
		return 0;
	}

	listNode *p = h->first; //����Ʈ��� ����ü������ p�� �����ϰ� ����Ʈ�� ù��° ��带 ����Ű���� ��
	listNode *tail = NULL; //����Ʈ��� ����ü������ tail�� �����ϰ� NULL�� �ʱ�ȭ

	if(p->link == NULL) //����Ʈ�� ��尡 �Ѱ��� ���� ���
	{
		h->first == NULL; //��尡 NULL�� ����Ű���� �Ͽ� ����Ʈ�� ���
		free(p); //��带 ���� �Ҵ� ����
		return 0;
	}

	while(p->link != NULL) //p�� link�� NULL�� �� ������ �ݺ�, ����Ʈ�� ������ ��带 ã�� ����
	{
		tail = p; //tail�� p�� ��ġ�� �̵�
		p = p->link; //p�� ���� ����� ��ġ�� �̵�
	}
	
	tail->link = NULL; //tail�� link�� NULL�� �ʱ�ȭ�Ͽ� ������ ��带 ����
	free(p); //p�� ����Ű�� ��带 ���� �Ҵ� ����
	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	if(h->first == NULL) //��尡 ����Ű�� ��尡 ��������� ����Ʈ�� �������
	{
		printf("������ ����Ʈ�� �����ϴ�.\n");
		return 0;
	}

	listNode *a = h->first; //b�� ���� ��带 ����ų ����ü������ a ����
	listNode *b = h->first; //c�� ���� ��带 ����ų ����ü������ b ����
	listNode *c = h->first; //����Ʈ�� ������ �̵��� ����ü������ c ����

	while(c != NULL) //c�� NULL�� �ƴϸ� �ݺ�, ����Ʈ�� ������ �ݺ��� �ǹ�
	{
	
		a = b; //a�� b�� ��ġ�� �̵�
		b = c; //b�� c�� ��ġ�� �̵�
		c = c->link; //c�� ���� ����� ��ġ�� �̵�
		b->link = a; //b�� link�� ���� ��带 ����Ű���� ��
	}

	h->first->link = NULL; //������ ���������� ���κ��� ����Ʈ�� ���̹Ƿ� NULL�� �ʱ�ȭ
	h->first = b; //b�� ������ġ�̹Ƿ� ��尡 b�� ����Ű���� ��

	return 0;
}

//����Ʈ ����ϴ� �Լ�
void printList(headNode* h) {
	int i = 0;
	listNode* p; //����Ʈ�� ��带 ����Ű�� ����ü ������ p

	printf("\n---PRINT\n");

	if(h == NULL) { //h�� NULL = ����Ʈ�� ������� ���
		printf("Nothing to print....\n"); 
		return;
	}

	p = h->first; //����Ʈ�� ù��° ��带 ����Ű���� ��

	while(p != NULL) { //p�� NULL�� �Ǹ� �ݺ��� ����
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i); //����Ʈ�� ��� ���� ���
}

