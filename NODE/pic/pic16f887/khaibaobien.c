UNSIGNED INT16 KQADC,AN0, AN1;
UNSIGNED INT8 CONFIG_FUN=0, ID_NODE = 0, STT_DEVICE=0, STT_SENSOR=0;
UNSIGNED INT8 VT=0, KYTU=0;// KYTU[30], 
UNSIGNED INT8 ID_NODE_NHAN, ID_DEVICE_NHAN, TT_DEVICE_NHAN;
//UNSIGNED INT8 ID_SENSOR_NHAN, TT_SENSOR_NHAN;
CHAR KYTUCHAR[20]="HIHI";
//CHAR *DATA_NHANDUOC[]={"IDGW","IDNODE","COMMAN","DATA"};
INT1 TTNHAN = 0, TT_CONFIG=0, TT_CONTROL=0,TT_CONFIG_DONE=0, TT_FUN=0, TT_STT=0;
INT1 TT_DEVICE[8]={0, 1, 1, 0, 1, 0, 1, 1};
INT1 TT_SENSOR[8]={1, 1, 1, 1, 0, 0, 0, 0};
CHAR *TT_DEVICE_CHAR[]="00000000";
CHAR *PACKAGE_NHIETDO[]={"*","ID_GW", "ID_NODE","LENGHT", "S_S" ,"TT_cambien","#"};

CHAR *PACKAGE_CONFIG[]={"*","ID_GW" ,"ID_NODE", "LENGHT","C_F", "DEVICE1234","SENSOR1234","#"};

CHAR *ID_[]="00";
//CHAR *ID_GW[]= "0000";
UNSIGNED INT8 ID_GATEWAY[4] = {0,0,0,0};
CHAR *TEMP_CHAR[]="00";
CHAR *TEMP_CHAR2[]="00000000"; 
CHAR *TEMP_CHAR3[]="0000"; 
UNSIGNED INT8 LEN_PACKAGES = 0;
CHAR NHIETDO1[]="27";
CHAR NHIETDO2[]="27";
