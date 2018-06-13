#include <stdio.h>
#include <stdlib.h>
#include <string.h>



enum script_type {
	TEMPERATURE = 'T',
	RELAY_NODE = 'R',
	ACTUATOR = 'A',
	FUNCTION_GENERATOR = 'F',
	DURATION = 'D',
	CYCLE = 'C',
};

#define MAX_TEMP_INDEX    5
#define MAX_NODE_INDEX    20
#define MAX_GENERATION_INDEX  3
struct script_cmd {
	int temp[MAX_TEMP_INDEX];
	char relay_node[MAX_NODE_INDEX]; /* relay node :max node is 20*/
	int actuator_step;
	int function_generation[MAX_GENERATION_INDEX];
	int duration;
	char  cycle;
};

#define VALUE_DELIMITER   (',')
#define TYPE_DELIMITER    (':')
#define CMD_DELIMITER     (';')

#define VALUE_DELIMITER_S   (",")
#define TYPE_DELIMITER_S    (":")
#define CMD_DELIMITER_S     (";")

/* |X:value;| */
char *find_cmd_value(char *onecmd)
{
	if(onecmd ==NULL)
		return NULL;
	while((*onecmd != TYPE_DELIMITER)&&(*onecmd != '\0')) {
		onecmd++;
	}
	return (onecmd+1);
}

char *get_cmd(char *script, struct script_cmd *cmd)
{
	char *save_script = NULL;
	char *onecmd;
	char *value_s;
	char *save_value_s;
	char *value;
	int size;
	

	while(1)  {
		onecmd = (char *)strtok_r((char *)script, CMD_DELIMITER_S, (char **)&save_script);
		if(onecmd == NULL)
			break;
		
		printf("onecmd=%s\n", onecmd);
		script = save_script;
		
		switch(onecmd[0]) {
			/* temperature type format: |--T---|-temp1-|-temp2-|-temp3-|-temp4-|-temp5-|
			* temperature type format: |T:-100,-200,-300,-400,-500;|
			*/
			case TEMPERATURE:
				value_s = find_cmd_value(onecmd);
				
				for(size = 0; size < MAX_TEMP_INDEX; size++) {
					value = strtok_r(value_s, VALUE_DELIMITER_S, &save_value_s);
					if(value ==NULL)
						break;
					value_s = save_value_s;
					
					
					cmd->temp[size] = atoi(value);
					printf("temp[%d]=%d\n", size, cmd->temp[size]);
				}
				break;
			
			/* relay node format : |--R-|NODE,NODE,NODE,......------------------------------------|
			 * relay node format : |R:10,20,30,40,50,60,10,20,30,40,50,60,10,20,30,40,50,60,50,60;|
			 */
			case RELAY_NODE:
				value_s = find_cmd_value(onecmd);
				
				for(size = 0; size < MAX_NODE_INDEX; size++) {
					value = strtok_r(value_s, VALUE_DELIMITER_S, &save_value_s);
					if(value ==NULL)
						break;
					value_s = save_value_s;
					
					cmd->relay_node[size] =  atoi(value);
					printf("relay_node[%d]=%d\n", size, cmd->relay_node[size]);
				}
				printf("\n\n");
				break;
			
			/* actuator format: |--A--|----value----|
			 * actuator format: |A:1000;|
			 */
			case ACTUATOR:
				value_s = find_cmd_value(onecmd);
				cmd->actuator_step = atoi(value_s);
				printf("actuator step = %d \n", cmd->actuator_step);
				break;
			
			/* function_generator format: |--40--|-wave|frequency|amplitude|
			 * function_generator format: |F:1,1000,100;|
			 */
			case FUNCTION_GENERATOR:
				value_s = find_cmd_value(onecmd);
				
				for(size = 0; size < MAX_GENERATION_INDEX; size++) {
					value = strtok_r(value_s, VALUE_DELIMITER_S, &save_value_s);
					if(value ==NULL)
						break;
					value_s = save_value_s;
					
					cmd->function_generation[size] = atoi(value);
				}
				

				printf("frequency  = %d \n", cmd->function_generation[1]);
				printf("AM = %d \n", cmd->function_generation[2]);
				printf("wave form = %d \n", cmd->function_generation[0]);
				break;
			
			/* duration format: |--D--|----value----|
			 * duration format: |D:10000|
			 */
			case DURATION:
				value_s = find_cmd_value(onecmd);
				cmd->duration = atoi(value_s);
				printf("duration  = %d \n", cmd->duration);
				break;
			
			/* cycle format: |--60--|----value----|
			 * cycle format: |-8bits|---8bits-----|
			 */
			case CYCLE:
				value_s = find_cmd_value(onecmd);
				cmd->cycle = atoi(value_s);
				printf("cycle  = %d \n", cmd->cycle);
				break;
			default:
				//error cmd
				printf("unknow cmd \n");
				break;			
		}
	}
	return onecmd;
}

int main(void)
{
	int i = 0xf;
	int ret = i<<8;
	printf("ret=0x%x\n", ret);
struct script_cmd cmd;
	char test[] = "T:-100,-200,-300,-400,-500;R:10,20,30,40,50,60,10,20,30,40,50,60,10,20,30,40,50,60,50,60;A:1000;F:1,1000,100;D:10000;C:100;";
//	get_cmd(test, &cmd);
	
}
