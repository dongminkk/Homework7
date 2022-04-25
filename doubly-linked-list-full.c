#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node { //노드 구조체 선언 데이터와 다음 주소를 가리키는 링크가 들어 있음
	int key; //데이터 
	struct Node* llink; // link 필드 자신과 동일한 타입을 가르켜야 함
	struct Node* rlink; // 이중 연결 리스트라서 링크가 두개 앞쪽 뒤쪽 연결
} listNode;

//이중 연결 리스트은 앞 뒤로 연결하여 앞으로도 갈수 있고 뒤로도 갈수있음

typedef struct Head {  // 처음 노드를 가르키는 first Head 구조체
	struct Node* first;  // 중첩 구조체
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h); //초기화

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h); //종료 동적 할당 해제

int insertNode(headNode* h, int key); // 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertLast(headNode* h, int key); // list에 key에 대한 노드하나를 마지막에 추가
int insertFirst(headNode* h, int key); // list 처음에 key에 대한 노드하나를 추가
int deleteNode(headNode* h, int key); /// list에서 key에 대한 노드 삭제
int deleteLast(headNode* h); // list의 마지막 노드 삭제
int deleteFirst(headNode* h); // list의 첫번째 노드 삭제
int invertList(headNode* h); // 리스트의 링크를 역순으로 재 배치

void printList(headNode* h); // 리스트를 출력


int main()
{
	char command; // 문자형 변수 선언
	int key; // int형 변수 선언 이중 연결 리스트에 넣을  데이터을 받음
	headNode* headnode=NULL; //처음 노드를 가르키는 first Head 구조체 선언
	printf("[----- [kim dongmin] [2017038093] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //기능 선택

		switch(command) {
		case 'z': case 'Z': //초기화 
			initialize(&headnode);
			break;
		case 'p': case 'P': //출력 리스트
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = "); // 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); //데이터 입력 받음
			deleteNode(headnode, key);  //list에서 key에 대한 노드 삭제
			break;
		case 'n': case 'N': 
			printf("Your Key = ");
			scanf("%d", &key); //데이터 입력 받음
			insertLast(headnode, key); //list에 key에 대한 노드하나를 마지막에 추가
			break;
		case 'e': case 'E': 
			deleteLast(headnode); // list의 마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); //데이터 입력 받음
			insertFirst(headnode, key); // list 처음에 key에 대한 노드하나를 추가
			break;
		case 't': case 'T':
			deleteFirst(headnode); // list의 첫번째 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode); //리스트의 링크를 역순으로 재 배치
			break;
		case 'q': case 'Q': 
			freeList(headnode); //종료 및 동적 할당 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //잘못입력에 대한 오류 처리
			break;
		}

	}while(command != 'q' && command != 'Q'); //'q' && 'Q' 이면 반복문 종료

	return 1;
}


int initialize(headNode** h) { //초기화 

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL) //조건문 h가 NULL이 아니면 할당된 메모리 모두 헤제
		freeList(*h); //할당한 메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode)); //동적 할당
	(*h)->first = NULL; // first  = NULL
	return 1; //1 리턴
}

int freeList(headNode* h){  // 할당한 메모리 해제
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; // listNode형 포인터 p에 첫번쩨 주소 h 대입

	listNode* prev = NULL; // listNode형 포인터 prev에 NULL 대입
	while(p != NULL) { //p 가 NULL이 아닐 때까지 반복
		prev = p;
		p = p->rlink;
		free(prev); //동적할당 해제
	} 
	free(h); //동적할당 해제
	return 0; //리턴 0
}


void printList(headNode* h) { // 리스트를 출력하는 함수
	int i = 0; //정수형 i 선언
	listNode* p; //listNode형 포인터 p 선언

	printf("\n---PRINT\n");

	if(h == NULL) { // Nothing to print 오류 처리
		printf("Nothing to print....\n"); //Nothing to print
		return;
	}

	p = h->first;  // p에 처음노드

	while(p != NULL) { //p가 NULL이 될 때까지 반복
		printf("[ [%d]=%d ] ", i, p->key); //i 번째 와 데이터 출력
		p = p->rlink; //다음 노드
		i++; //i값 증가
	}

	printf("  items = %d\n", i); //노드의 갯수
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {  // list에 key에 대한 노드하나를 마지막에 추가

	listNode* node = (listNode*)malloc(sizeof(listNode)); //동적할당 
	node->key = key; //노드에 key 데이터를 받음
	node->rlink = NULL; // rlink 링크 NULL 다음
	node->llink = NULL; // llink 링크 NULL 

	if (h->first == NULL) //처음 노드 가 없으면 첫번째에 넣어줌
	{
		h->first = node; // 노드를 첫번째에다 넣음
		return 0; //리턴 0
	}

	listNode* n = h->first; // listNode형 포인터 n 선언 하고 first을 넣음
	while(n->rlink != NULL) { //link가 NULL이 맞을 때까지 반복
		n = n->rlink; //마지막 노드 찾기
	}
	n->rlink = node; //n의 rlink가 node를 가리킴
	node->llink = n; // 추가한 노드의 llink가 n을 가리킴
	return 0; //리턴 0
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) { //list의 마지막 노드 삭제하는 함수

	if (h->first == NULL) // //노드가 없을때 오류 
	{
		printf("nothing to delete.\n"); // nothing to delete. 지울게 없음
		return 0; //리턴 0
	}

	listNode* n = h->first; // listNode형 포인터 n 선언 하고 first을 넣음
	listNode* trail = NULL; //구조체 선언 trail
 
	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) { //rlink == NULL인경우
		h->first = NULL; // first = NULL
		free(n); //동적할당 해제
		return 0;// 리턴 0
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) { //널이 될때까지 반복
		trail = n; //trail = n
		n = n->rlink; //마지막 노드 찾기
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL; // 이전 노드의 링크 NULL 처리
	free(n); //동적할당 해제

	return 0; // 리턴 0
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {// list 처음에 노드하나를 추가 하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode)); //동적할당
	node->key = key; //노드에 key 데이터를 받음
	node->rlink = node->llink = NULL; // rlink, llink=널

	if(h->first == NULL) //노드가 없을때
	{
		h->first = node; //지금 추가한 노드 가 first
		return 1;// 리턴 1
	}

	node->rlink = h->first; // 원래 가르키던 노드를 지금 추가한 노드가 가르키게 함
	node->llink = NULL; //이전 노드 링크가 없음

	listNode *p = h->first; //구조체 포인터 선언 첫번째에 있었던 노드를 가리 킴
	p->llink = node; // 첫번째에 있었던 노드 가 밀리고 이전노드로 추가한 노드를 가리침
	h->first = node; ///처음 주소에 node을삽입

	return 0;// 리턴 0
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) { //첫번째 노드 삭제하는 함수

	if (h->first == NULL) //노드가 없을때 오류 처리
	{
		printf("nothing to delete.\n"); //nothing to delete.
		return 0;
	}
	listNode* n = h->first; // 첫번째 노드
	h->first = n->rlink; //이전 노드를 첫번째로 가리킴

	free(n); // 동적 할당 해제

	return 0; //리턴 0
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) { //리스트의 링크를 역순으로 재 배치하는 함수


	if(h->first == NULL) { //노드가 없을때 오류 처리
		printf("nothing to invert...\n"); //nothing to invert.
		return 0; //리턴 0
	}
	listNode *n = h->first; // listNode형 포인터 n 선언 첫번째 노드를 포인트
	listNode *trail = NULL; // listNode형 포인터 trail 선언
	listNode *middle = NULL; // listNode형 포인터 middle 선언

	while(n != NULL){ //널이 될때까지 반복
		trail = middle; //trail에 middle저장
		middle = n; //middle 에 n
		n = n->rlink; //다음 n이 가리키고 있는 노드
		middle->rlink = trail; //  rlink링크 역순
		middle->llink = n; //  llink링크 역순
	}

	h->first = middle; // middle가 처음 노드

	return 0; //리턴 0
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //동적할당
	node->key = key; //노드에 key 데이터를 받음
	node->llink = node->rlink = NULL; // 이전, 다음 링크 NULL
 
	if (h->first == NULL) //첫번째 일때 
	{
		h->first = node; // 노드를 첫번째에다 넣음
		return 0; //리턴 0
	}

	listNode* n = h->first; //listNode형 포인터 n 선언 후 first 대입

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { // n이 NULL이 맞을 때까지 반복
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				insertFirst(h, key);
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
			}
			return 0; //리턴 0
		}

		n = n->rlink; //다음 링크
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) { //list에서 key에 대한 노드 삭제하는 함수

	if (h->first == NULL) //노드가 없을때 오류 처리
	{
		printf("nothing to delete.\n");
		return 1; //리턴 1
	}

	listNode* n = h->first; // listNode형 포인터 n 선언 하고 first을 넣음

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); //첫번째 노드 삭재
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h); //마지막 노드 삭제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n); //동적 할당 해제
			}
			return 1; //리턴 1
		}

		n = n->rlink; //이전 노드의 링크 삽입
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1; //리턴 1
}