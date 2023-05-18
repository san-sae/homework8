/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  School of Computer Science
 *  at Chungbuk National University
 *
 */

#include<stdio.h>
#include<stdlib.h>

// 노드에 대한 구조체 정의
typedef struct Node {
	int key; // 데이터
	struct Node* llink; // 왼쪽 링크
	struct Node* rlink; // 오른쪽 링크
} listNode; // 별칭(= struct Node)

// 프로토 타입
/* initialize() 함수에서 'h'를 전달받을 때 이중포인터를 이용하여
   함수 내에서 'h'에 대한 변경 가능
*/
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);

int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);

int main(){
	char command; // 수행할 코맨드
	int key; // 입력할 key값을 저장할 변수
	listNode* headnode=NULL; // 헤더노드를 NULL로 초기화

    printf("[----- [ChoiYoolim] [2020022001] -----]");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 사용자의 코맨드 입력

		switch(command) { // 입력받은 코맨드에 대한 switch문
		case 'z': case 'Z':
			initialize(&headnode); // 원형 연결리스트 초기화 
			break;
		case 'p': case 'P':
			printList(headnode); // 원형 연결리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); // 삽입할 노드의 key값 입력
			insertNode(headnode, key); // 크기 순에 따른 노드 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);// 삭제할 노드의 key값 입력
			deleteNode(headnode, key); // 입력한 key값과 같은 key값을 가진 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); // 삽입할 노드의 key값 입력
			insertLast(headnode, key); // 헤더노드의 왼쪽에 노드 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode); // 헤더노드의 왼쪽 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); // 삽입할 노드의 key값 입력
			insertFirst(headnode, key); // 헤더노드 오른쪽에 노드 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode); // 헤더노드의 오른쪽 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode); // 원형 연결리스트 순서를 역
			break;
		case 'q': case 'Q':
			freeList(headnode); // 원형 연결리스트에 대한 동적할당 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 그 이외의 코맨드는 유효한 코맨드가 아님
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

// 원형 연결리스트를 초기화하는 함수
int initialize(listNode** h) {
	
	if(*h != NULL) // 헤더노드가 NULL이 아닐 경우
		freeList(*h); // 링크드리스트에 대한 동적 메모리 해제

	*h = (listNode*)malloc(sizeof(listNode)); // 헤더노드에 대한 동적 할당
	(*h)->rlink = *h; // 헤더노드(마지막노드)의 rlink가 헤더노드 자체를 가리키도록 설정
	(*h)->llink = *h; // 헤더노드(첫번째노드)의 llink가 헤더노드 자체를 가리키도록 설정
	(*h)->key = -9999; // 헤드노드(값 저장이 아닌 시작점을 알리는 역할)의 key필드에 임의의 값 할당
	return 1;
}

// 메모리 해제 함수
int freeList(listNode* h){

	if(h->rlink == h){ // 노드가 없는 경우
		free(h); // 헤드 노드에 대한 동적 할당 해제
		return 1;
	}

	listNode* p = h->rlink; // 현재 노드를 가르키는 포인터
	listNode* trail = h; // 이전 노드(삭제할 노드)를 가리키는 포인터

	while (p != h) { // 헤더노드가 아닐 때 반복
		trail = p; // 현재 노드를 이전 노드로 설정
		p = p->rlink; // 현재 노드를 다음 노드로 설정
		free(trail); // 이전 노드에 대한 동적할당 해제
	}

	free(h); // 헤더노드에 대한 동적할당 해제

	return 0;
}

// 리스트 출력 함수
void printList(listNode* h) {
	int i = 0;
	listNode* p; // 현재노드를 가리키는 포인터

	printf("\n---PRINT\n");

	if(h == NULL) { // 헤더노드 자체가 할당된 메모리가 아닐 경우 
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; // 헤더노드가 p를 가리키도록 설정

	while(p != NULL && p != h) { // 노드 p가 비어있지 않으며 헤더노드가 아닐 경우
		printf("[ [%d]=%d ] ", i, p->key); // [ [i]=i번째 노드의 key값 ] 형식으로 출력
		p = p->rlink; // p가 다음노드를 가리키도록 설정
		i++;
	}
	printf("  items = %d\n", i); // 전체 노드의 개수 출력


	/* print addresses : 헤더노드의 llink, 헤더노드 자체의 주소, 헤더노드의 rlink */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink; // p가 첫번째 노드가 되도록 설정
	while(p != NULL && p != h) { // 노드 p가 비어있지 않으며 헤더노드가 아닐 경우
		/* print addresses : 노드의 key값, 노드의 llink, 노드의 rlink */
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink; // p에 p의 다음 노드가 되도록 설정
		i++;
	}

}

// 노드를 마지막 위치에 삽입 함수
int insertLast(listNode* h, int key) {

	if(h == NULL) { // 헤더노드 자체가 할당된 메모리가 아닐 경우 
		printf("Nothing to allocate....\n");
		return 1;
	}

	// 삽입할 노드에 대한 동적 할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	// 노드 안의 key값, 링크들에 대한 값 초기화
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;

	if(h->rlink == h){ // 노드가 없을 경우
		// 헤더노드의 두 링크를 node와 연결
		h->llink = node;
		h->rlink = node;
		// node의 두 링크를 헤더노드와 연결
		node->llink = h;
		node->rlink = h; 
		
		return 0;
	} 

	listNode* trail = h->llink; // 이전 노드

	node->llink = trail; // node의 llink를 이전 노드와 연결
	node->rlink = h; // node의 rlink를 헤더노드와 연결
	trail->rlink = node; // 이전노드의 rlink를 node와 연결
	h->llink = node; // 헤더노드의 llink를 node와 연결
	
	return 1;
}

// 마지막 노드 삭제 함수
int deleteLast(listNode* h) {
	if(h == NULL){ // 연결리스트가 존재하지 않는 경우
		printf("Nothing to allocate...\n");
		return 1;
	}

	if(h->rlink == h){ // 노드가 없는 경우
		printf("Nothing to delete....\n");
		return 1;
	}

	listNode* trail = h->llink; // trail가 마지막 노드의 주소로 설정
	listNode* p = trail->llink; // p가 삭제할 마지막 노드의 이전 노드로 설정

	p->rlink = h; // 이전 노드의 오른쪽을 헤더노드와 연결
	h->llink = p; // 헤더노드의 왼쪽과 이전노드를 연결

	free(trail); // 마지막 노드에 대한 동적 할당 해제

	return 0;
}

// 노드를 첫 번째 위치에 삽입 함수
int insertFirst(listNode* h, int key) {

	if(h == NULL){ // 연결리스트가 존재하지 않는 경우
		printf("Nothing to allocate...\n");
		return 1;
	}

	// 삽입할 노드에 대한 동적 할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	// 노드 안의 key값, 링크들에 대한 값 초기화
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;

	if(h->rlink == h){ // 노드가 없는 경우
		// node를 기준으로 헤더노드 연결
		node->llink = h; 
		node->rlink = h;
		// 헤더노드를 기준으로 node 연결
		h->llink = node;
		h->rlink = node;

		return 0;
	}

	listNode* trail = h->rlink; // 이전노드

	node->llink = h; // 삽입할 노드(node)와 헤더노드 연결
	node->rlink = trail; // node와 이전 노드 연결
	trail->llink = node; // 이전 노드와 삽입노드 연결
	h->rlink = node; // 헤더노드와 노드 연결

	return 0;
}

// 첫번째 노드 삭제
int deleteFirst(listNode* h) {

	if(h == NULL){ // 연결리스트가 존재하지 않는 경우
		printf("Nothing to allocate...\n");
		return 1;
	}

	if (h->rlink == h) { // 노드가 없는 경우
		printf("Nothing to delete....\n");
		return 1;
	}

	listNode* first = h->rlink; // 삭제할 노드
	listNode* next = first->rlink; // 삭제할 노드의 다음 노드(두번째 노드)

	h->rlink = next; // 두번째 노드와 헤더노드의 오른쪽 링크를 연결하여 첫번째 노드 삭제
	next->llink = h; // 두번째 노드와 헤더노드 연결 

	free(first); // 첫번째 노드에 대한 동적 할당 해제

	return 0;
}

// 원형 연결리스트의 순서를 역으로 나열하는 함수
int invertList(listNode* h) {

	if(h == NULL){ // 연결리스트가 존재하지 않는 경우
		printf("Nothing to allocate...\n");
		return 1;
	}

	if (h->rlink == h) { // 노드가 없는 경우
		printf("Nothing to invert....\n");
		return 1;
	}

	listNode* node = h->rlink; // 헤더노드의 다음 노드가 node가 되도록 설정
	listNode* next = h; // 다음 노드
	listNode* trail = h; // 이전 노드


	while (node != h) { // 노드가 헤더노드와 다를 경우 반복
	next = node->rlink; // 현재노드의 다음노드
	node->rlink = trail; // 현재노드와 이전노드의 링크 전환
	node->llink = next; // 현재노드와 다음노드의 링크 전환
	trail = node; // 처리한 현재노드를 이전노드로 설정
	node = next; // 다음노드를 다음 루프에서 처리할 현재노드로 설정
	}

	h->rlink->llink = h; // 첫번째 노드와 헤더노드 연결
	// 역순의 원형 연결리스트에 맞게 헤더노드 연결
	h->llink = trail;
	h->rlink = trail;

	return 0;
}

// 입력받은 key값에 따른 노드 삽입 함수
int insertNode(listNode* h, int key) {

	if(h == NULL){ // 연결리스트가 존재하지 않는 경우
		printf("Nothing to allocate...\n");
		return 1;
	}

	// 삽입할 노드에 대한 동적할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	// 노드 안의 key값, 링크들에 대한 값 초기화
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;

	// 노드가 없는 경우
	if (h->rlink == h){
		insertFirst(h, key); // 첫 노드 삽입 함수
		return 0;
	}

	listNode* p = h->rlink; // 첫 노드

	while(p != NULL && p != h) { // 노드가 없지 않고 노드가 첫 노드가 아닐 경우
		if(p->key >= key) { // 현재노드의 key보다 삽입할 노드의 key값이 작거나 같은 경우
			if(p == h->rlink) { // p가 첫 노드일 경우
				insertFirst(h, key); // 첫 노드 삽입 함수
			} 
			else { // 현재노드의 key값이 삽입할 노드의 key값보다 큰 경우
				// 삽입할 노드를 기준으로 두 링크 설정
				node->rlink = p;
				node->llink = p->llink;
				p->llink->rlink = node; // 이전노드의 오른쪽과 현재노드 연결
				p->llink = node; // 현재노드를 이전노드로 설정
			}
			return 0;
		}
		p = p->rlink; // 다음으로 처리할 노드를 현재노드로 설정
	}

	insertLast(h, key); // 마지막 노드 삽입 함수

	return 0;
}

// 입력받은 key값과 동일한 key값을 가진 노드 삭제 함수
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL){ // 노드가 없거나 연결리스트에 대한 동적할당이 없는 경우
		printf("nothing to delete....\n");
		return 0;
	}

	listNode* p = h->rlink; // 현재노드 

	while(p != NULL && p != h) { // 현재노드가 존재하거나 헤더노드가 아닐 경우 반복
		if(p->key == key) { // 현재노드의 key값이 삽입할 key값과 동일한 경우
			if(p == h->rlink) { // 현재노드가 첫 노드일 경우
				deleteFirst(h);
			}
			else if (p->rlink == h){ // 다음노드가 헤더노드일 경우(현재노드가 마지막 노드일 경우)
				deleteLast(h); // 마지막 노드 삭제 함수
			}
			else { // 중간에 위치한 노드일 경우
				// 현재 노드를 삭제하기 위한 연결 수정
				p->llink->rlink = p->rlink; 
				p->rlink->llink = p->llink; 
				free(p); // 현재노드에 대한 동적할당 해제
			}
			return 0;
		}
		p = p->rlink; // 다음에 처리할 노드를 현재노드로 설정
	}

	printf("cannot find the node for key = %d\n", key); // key값을 가진 노드를 찾을 수 없음
	return 0;	
}
