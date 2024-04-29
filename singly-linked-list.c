/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
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
		printf("---------------[2023041039]-----[최나현]------------------------\n");
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

	return 1;
}

//headnode 초기화하는 함수
headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeList를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

//리스트 메모리 해제하는 함수
int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; 

	listNode* prev = NULL; //이전 노드를 가리킬 구조체 포인터 prev 생성
	while(p != NULL) { //p가 NULL이 될 때까지 동적 할당을 해제
		prev = p; 
		p = p->link; 
		free(prev);
	}
	free(h); //헤드도 동적 할당을 해제해준다.
	return 0;
}



/*
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode 구조체 크기만큼을 동적 할당
	node->key = key; //입력받은 key값을 노드의 key에 저장

	node->link = h->first; //노드의 link는 헤드가 가리키는 노드를 가리킴
	h->first = node; //헤드가 새로 생성한 노드를 가리키도록 함

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key)
{	//노드 생성부분
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if(h->first == NULL) // 헤드가 아무것도 가리키지 않는다면 == 리스트가 비어있다면
	{
		h->first = node; // 헤드는 새로 생성한 노드를 가리킴
		return 0;
	}
	// 리스트가 비어있지 않다면
	listNode* p = NULL; //리스트를 검색할 구조체포인터 p생성
	listNode* tail = NULL; // 항상 p보다 한 노드 뒤에있을 구조체 포인터 tail 생성
	// 초기에 p와 tail은 헤드와 같은 노드를 가리킴
	p = h->first; 
	tail = h->first;

	while(p != NULL) //p가 NULL일 때까지 반복
	{
		if(p->key >= key) // 만약 입력받은 key 값이 p가 가리키는 key값보다 작다면
		{
			if(p == h->first) // 리스트에 노드가 한개 있을 경우
			{
				// 리스트의 처음부분에 노드를 위치시킴
				h->first = node; 
				node->link = p;
			}
			else // 리스트에 노드가 여러개 있을 경우
			{
				node->link = p; // 새 노드는 p를 가리킴
				tail->link = node; //p의 이전 노드는 새 노드를 가리킴
			}
			return 0;
		}
		tail = p; // tail을 p의 위치로 이동
		p = p->link; // p를 다음 노드의 위치로 이동
	}
	//입력받은 key값보다 큰 값의 노드가 없을 경우
	tail->link = node; // 리스트의 가장 마지막 노드가 새 노드를 가리킴 
	
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key)
{
	listNode* node = (listNode*)malloc(sizeof(listNode)); //리스트노드 구조체 크기만큼 동적 할당
	node->key = key; //입력받은 key값을 노드의 key에 저장
	node->link = NULL; //노드의 link는 NULL로 초기화

	if(h->first == NULL) // 리스트가 비어있을 경우
	{
		h->first = node; // 헤드가 새로 생성한 노드를 가리키도록 함
		return 0;
	}
	
	listNode* p = NULL; //구조체포인터 p를 생성하고 NULL로 초기화
	p = h->first; //p가 리스트의 첫번째 노드를 가리키도록 함

	while(p->link != NULL) //p의 link가 NULL이 될 때까지 반복, 리스트의 마지막 노드를 찾는 과정
	{
		p = p->link; 
	}
	
	p->link = node; //p의 link가 새로 생성한 노드를 가리키도록 함

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) 
{

	if(h->first == NULL) // 헤드가 가리키는 노드가 비어있으면 리스트가 비어있음
	{
		printf("삭제할 리스트가 없습니다.\n");
		return 0;
	}
	
	
	listNode* p = NULL; //리스트노드 구조체포인터 p를 생성하고 NULL로 초기화

	p = h->first; //p가 리스트의 첫번째 노드를 가리키도록 함 
	h->first = p->link;	//헤드가 NULL을 가리키도록 함
	free(p); //p가 가리키는 노드를 동적 할당 해제

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	if(h->first == NULL)
	{
		printf("삭제할 리스트가 없습니다.\n");
		return 0;
	}

	listNode* p = NULL;
	listNode* tail = NULL;
	p = h->first;
	tail = h->first;

	while(p != NULL)
	{
		if(p->key == key)
		{
			if(p == h->first)
			{
				h->first = p->link;
				free(p);
				return 0;
			}
			
			tail->link = p->link;
			free(p);
			return 0;
		}
		
		tail = p;
		p = p->link;

	}

	printf("cannot find node for key.\n");	
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if(h->first == NULL)
	{
		printf("삭제할 리스트가 없습니다.\n");
		return 0;
	}

	listNode *p = h->first;
	listNode *tail = NULL;

	if(p->link == NULL)
	{
		h->first == NULL;
		free(p);
		return 0;
	}

	while(p->link != NULL)
	{
		tail = p;
		p = p->link;
	}
	
	tail->link = NULL;
	free(p);
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	if(h->first == NULL)
	{
		printf("역순할 리스트가 없습니다.\n");
		return 0;
	}

	listNode *a = h->first;
	listNode *b = h->first;
	listNode *c = h->first;

	while(c != NULL)
	{
	
		a = b;
		b = c;
		c = c->link;
		b->link = a;
	}

	h->first->link = NULL;
	h->first = b;

	return 0;
}

//리스트 출력하는 함수
void printList(headNode* h) {
	int i = 0;
	listNode* p; //리스트의 노드를 가리키는 구조체 포인터 p

	printf("\n---PRINT\n");

	if(h == NULL) { //h가 NULL = 리스트가 비어있을 경우
		printf("Nothing to print....\n"); 
		return;
	}

	p = h->first; //리스트의 첫번째 노드를 가리키도록 함

	while(p != NULL) { //p가 NULL이 되면 반복을 멈춤
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i); //리스트의 노드 개수 출력
}

