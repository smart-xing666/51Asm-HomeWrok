CRLF equ 0dh,0ah

;�ϵ�����
TYPE_BROKE_NORMAL 	equ 0
TYPE_BROKE_HARD		equ 1
TYPE_BROKE_MEMORY	equ 2

cs_insn struc				;c++�нṹ����룬��������Ĵ�СҪ����Ӧ����
	id		dd ?		;���
	address		dq ?		;��ַ
	csize   	dd ?		;��С
	bytes		db 18 dup(?)	;����
	mnemonic	db 32 dup(?)	;ǰ׺
	op_str		db 162 dup(?)	;������
	pcs_detail	dd ?		;��ϸ
cs_insn ends

pt_info union
	oldCode		db ?	;�ϵ���ǰֵ
	nPage		dd ?	;�ϵ��ҳ
	nDRNum		dd ?	;���Ӳ���ϵ�λ��
pt_info ends

pt_broke struc
	pAddr		dd ?	;��ַ
	isOnce		dd ?	;һ����
	nSize		dd ?	;�ϵ�ߴ�
	cType		dd ?	;�ϵ�����
	dwOldType	dd ?	;֮ǰ��ҳ������
	Other		pt_info<>
pt_broke ends

DebugLoop proto								;�쳣��Ϣѭ��
OnExceptionEvent proto pDE:ptr DEBUG_EVENT				;�쳣�¼�����
OnProcessCreateEvent proto pDE:ptr DEBUG_EVENT				;���̴����¼�

DisAsmEngineInit proto c						;����������ʼ��
DisAsmEngineDestory proto c						;�������������
GetDisAsm proto c buff:dword,caddr:dword,csize:dword,count:dword	;�����
FreeDisAsmInfo proto c							;�ͷŷ�����ڴ�
DoDump proto c PathName:ptr byte,hprocess:HANDLE,dwBaseOfImage:dword	;Dump
DoDumpEx proto

GetDRNum proto
SetTF proto								;���õ�����־λ
DecEIP proto								;EIP-1
GetEip proto								;��ȡ��ǰEIP
MyReadProcessMemory proto address:dword,csize:dword			;��ȡ�ڴ�
MyWriteProcessMomory proto address:dword,csize:dword			;д���ڴ�
AddBrokePoint proto PointInfo:ptr pt_broke				;����ϵ�

SetStepInto proto							;�趨����
SetStepOver proto							;�趨����
SetBrokePoint proto pos:dword,isOnce:dword				;����һ��ϵ�
SetHardBrokePoint proto pos:dword,len:dword,ctype:dword			;����Ӳ���ϵ�
SetMemoryBrokePoint proto pos:dword,len:dword,ctype:dword		;�����ڴ�ϵ�

RemoveBrokePointEx proto Hint:dword					;ɾ���ϵ㣬�Զ��ж϶ϵ�����

PrintBlank proto num:dword						;��ӡ�հ���
PrintDisAsm proto pcs_insn:ptr cs_insn,count:dword			;��ӡ�����
PrintDisAsmEx proto address:dword, count:dword				;��ӡ�����Ex
PrintData proto address:dword						;��ӡ����
PrintReg proto								;��ӡ�Ĵ���
PrintBrokePointTable proto BPType:dword					;��ӡһ��ϵ��
PrintMoudleTable proto

CommandForSetTypePoint proto pCommand:ptr byte,IsHardOrMemory:dword	;����Ӳ�����ڴ�ϵ�ָ��

RemoveOrSetHardPoint proto nDRNum:dword,isRomove:dword			;Ӳ���ϵ㿪��
RemoveOrSetMemoryPoint proto pPoint:ptr pt_broke			;�ڴ�ϵ㿪��
CommandForSetMemory proto pCommand:ptr byte				;�ڴ�ϵ㿪��

ReadScriptFile proto
ReadOneCommand proto
SaveOneCommand proto
SaveScriptFile proto


.data
g_hProcess dd 0
g_dwThreadID dd 0
g_CodeBuffer db 200 dup(0)
g_pBreakPointArray dd 40 dup(0)
g_bIsExit dd 0
g_CCStepAddr dd 0					
g_bIsStep dd 0								;��������
g_nDRNum dd 0
g_MemHint dd 0	
g_CCResetAddr dd 0
g_pFILE dd 0
g_bScript dd 0								;�ű���־
g_Teb dd 0
g_dwBaseOfImage dd 0