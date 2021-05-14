typedef struct
{
    char bankName[100];
    customerAVLtree *ctree;
    staffAVLtree *stree;
}Bank;


void customerDetails(Customer *customer)
{
	printf("\n\n***********DETAILS***********\n\n");
	printf("Name : %s\n",customer->cName);
	printf("Account number : %ld\n",customer->cId);
	printf("Email : %s\n",customer->cAddress);
	printf("Balance : Rs.%f\n",customer->cBalance);
}

void deposit(Customer *customer, float amount)
{
	if(amount>100000)
	{
		printf("\nMaximum deposit limit exeeded, deposit a lower amount!");
	}
	else
	{
		customer->cBalance+=amount;
		printf("\nAmount deposited SUCCESSFULLY!\nNew Balance: %f",customer->cBalance);
	}
}

void withdraw(Customer *customer, float amount)
{
	if((customer->cBalance-amount)>1000 && amount<100000)
	{
		customer->cBalance-=amount;
		printf("\nAmount withdrawn SUCCESSFULLY!\nNew Balance: %f",customer->cBalance);
	}
	else
	{
		printf("\nInsufficient balance, withdraw a lower amount!\nCurrent Balance : %f",customer->cBalance);
	}
}

void transfer(Bank *B,Customer *customer, long acc,float amount)
{
	Customer *recipient;
	recipient=searchCustomerAVL(B->ctree,acc);
	if((customer->cBalance-amount) >1000 && amount<500000)
	{

		recipient=searchCustomerAVL(B->ctree,acc);

		if(recipient==NULL)
		{
			printf("\n\nRecipient account number invalid!!");
			return;
		}

		else
		{
			customer->cBalance-=amount;
			recipient->cBalance+=amount;
			printf("\n\nAmount Rs.%f tranferred to account number %ld SUCCESSFULLY",amount,acc);
		}
		
	}
	else if(customer->cBalance-amount>1000)
	{
		printf("\n\nInsufficient balance, could not transfer amount!\nCurrent Balance : %f",customer->cBalance);
	}
	else
	{
		printf("\n\nMaximum transfer amount of Rs.5,00,000 exeeded, transfer a lower amount !");	
	}
}

void createQueue(Bank *B,priorityQueueADT *pq)
{
    int i;
    srand(time(0));
    Customer *customer;
    long acc;
    for(i=0;i<5;++i)
    {
        acc=(rand()%(185001114-185001100))+185001100;
        customer=searchCustomerAVL(B->ctree,acc);

        enqueue(pq,customer);
    }

   // displayQueue(pq,1,0);
}

void staffMenu(Bank *B,Staff *staff)
{
	Customer *customer;
	int choice;
	float amount;
	long acc;
    staff->queue=malloc(sizeof(priorityQueueADT));
    init(staff->queue);
    createQueue(B,staff->queue);
    while(!emptyQueue(staff->queue))
    {
    	customer=dequeue(staff->queue);
    	choice =0;
    	while(choice != 5)
    	{
	  		printf("\n\t\tCurrent customer : %s\n",customer->cName);
	  		printf("\n\t\t***********MENU***********\n");
	    	printf("\n1) View customer details\n2) Deposit money\n3) Withdraw money\n4) Transfer money \n5) Next customer\n6) View bank database\nEnter choice: ");
    		scanf("%d",&choice);
    		switch(choice)
    		{
    			case 1:
    				customerDetails(customer);
    				break;

    			case 2:
    				printf("\n\nEnter amount to deposit in Rs. :\n");
    				scanf("%f",&amount);
    				deposit(customer,amount);
    				break;

    			case 3:
    				printf("\n\nEnter amount to Withdraw in Rs. :\n");
    				scanf("%f",&amount);
    				withdraw(customer,amount);
    				break;

    			case 4:
    				printf("\n\nEnter recipient account number:");
    				scanf("%ld",&acc);
    				printf("\n\nEnter amount to tranfer :");
    				scanf("%f",&amount);
    				transfer(B,customer,acc,amount);
    				break;

                case 5:
                    continue;
                    break;

                case 6:
                    printf("\n\nName\t\t\tAccount No\tEmailID\t\t\t\tAge\t\tBalance\n_______________________________________________________________________________________________________\n");
                    displayCustomer(B->ctree);
                    break;
    		}
    	}
    }
}

void staffLogin(Bank *B)
{
    Staff *staff;
    staff = NULL;
    long sID;
    char sPassword[50];
	printf("\n\n\t\t**********LOGIN*********\n\n");
	printf("Enter staff ID :\n");
	scanf("%d",&sID);
	printf("Enter Password :\n");
	scanf("%s",sPassword);
    staff = searchStaffAVL(B->stree,sID);

    if(staff != NULL)
    {
        if(strcmp(staff->sPassword,sPassword) == 0)
        {
            printf("\n\n\t\tLOGIN SUCCESSFULL!!\n\n");
            staffMenu(B,staff);
        }
        else
        {
            printf("\n\n\t\tINVALID USERNAME OR PASSWORD!\n\n");
        }
    }
    else
    {
        printf("\n\n\t\tINVALID USERNAME OR PASSWORD!\n\n");
    }

}

void setData(Bank *B)
{
	Customer customer;
	Staff staff;
	B->ctree = NULL;
	B->stree = NULL;
	long sId[] = {1100,1101,1102,1103,1104,1105,1106,1107,1108,1109};
    char spass[][50] =  {"staff00","staff01","staff02","staff03","staff04","staff05","staff06","staff07","staff08","staff09"};
    int age[]={18,24,56,78,35,51,25,67,40,67,21,46,55,19,32};
    char cName[][50] = {"Tom James","Brent Morey","Shawn Calvin","Harr Steve","Dave Floyd","Milli Brown","Misato Ippo","Harry Potter","Simba Pim","Gordon Ramsay","Ant man    ","Hulk      ","Robert Patt","Scott Lang","Rupert Grint"}; 
    //long cId[] = {2222344,3345511,3311245,5566778,1100223,3344552,1546102,7712834,2435465,5613029}; 
    long cId[] = {185001100,185001101,185001102,185001103,185001104,185001105,185001106,185001107,185001108,185001109,185001110,185001111,185001112,185001113,185001114};
    char cAddress[][50] = {"tom_21@gmail.com","brent_morey@gmail.com","shawn_cal12@yahoo.com","kit__harr@gmail.com","dave_00@hotmail.com","millibrown@gmail.com","misato__@gmail.com","harry_potter@yahoo.com","simba2000@gmail.com","opaqueman6@gmail.com","antman@gmail.com","hulk200@gmail.com","robert1@gmail.com","scottlang@yahoo.com","rupertGrint@gmail.com"}; 
    char cpass[][50] = {"tom_21","brent_morey","shawn_cal12","kit__harrington","dave_00","millibrown","misato__","harry_potter","simba2000","opaqueman6","antman","hulk","robert","scott","rupert"};
    float cBalance[]={18000,34012,56999,1600000,4512320,5060609,9989992,25000,2778768,3100000,5000000,560000,20000000,790000,45000};

    for(int i=0;i<10;++i)
    {
    	strcpy(customer.cName,cName[i]);
    	customer.cId=cId[i];
    	strcpy(customer.cAddress,cAddress[i]);
    	customer.cId = cId[i];
    	customer.age=age[i];
    	customer.cBalance = cBalance[i];
    	B->ctree = insertCustomer(B->ctree,customer);
    	staff.sID = sId[i];
    	strcpy(staff.sPassword,spass[i]);
    	B->stree = insertStaff(B->stree,staff);
    }

    for(int i=10;i<15;++i)
    {
        strcpy(customer.cName,cName[i]);
        customer.cId=cId[i];
        strcpy(customer.cAddress,cAddress[i]);
        customer.cId = cId[i];
        customer.age=age[i];
        customer.cBalance = cBalance[i];
        B->ctree = insertCustomer(B->ctree,customer);
    }
}