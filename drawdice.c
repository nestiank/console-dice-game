void drawDice(int _i, int _number)
{
	switch (_i)
	{
	case 1:
		printf("¦£¦¡¦¡¦¡¦¤");
		break;
	case 2:
		switch (_number)
		{
		case 0:
			printf("¦¢      ¦¢");
			break;
		case 1:
		case 2:
			printf("¦¢      ¦¢");
			break;
		case 3:
			printf("¦¢    ¡Ü¦¢");
			break;
		case 4:
		case 5:
		case 6:
			printf("¦¢¡Ü  ¡Ü¦¢");
			break;
		}
		break;
	case 3:
		switch (_number)
		{
		case 0:
			printf("¦¢      ¦¢");
			break;
		case 1:
		case 3:
		case 5:
			printf("¦¢  ¡Ü  ¦¢");
			break;
		case 2:
		case 6:
			printf("¦¢¡Ü  ¡Ü¦¢");
			break;
		case 4:
			printf("¦¢      ¦¢");
			break;
		}
		break;
	case 4:
		switch (_number)
		{
		case 0:
			printf("¦¢      ¦¢");
			break;
		case 1:
		case 2:
			printf("¦¢      ¦¢");
			break;
		case 3:
			printf("¦¢¡Ü    ¦¢");
			break;
		case 4:
		case 5:
		case 6:
			printf("¦¢¡Ü  ¡Ü¦¢");
			break;
		}
		break;
	case 5:
		printf("¦¦¦¡¦¡¦¡¦¥");
		break;
	}
}
