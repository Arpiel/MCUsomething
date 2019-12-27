LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE ieee.std_logic_unsigned.all;
ENTITY MAP1 IS
GENERIC( CLOCK:INTEGER :=50000000;
			PWM_CLOCK:INTEGER :=50;
			resolution:INTEGER :=10;
			phases:INTEGER :=1);
PORT( CLKIN:IN STD_LOGIC;
		reset:IN STD_LOGIC;
		PWM:OUT STD_LOGIC_VECTOR(phases-1 DOWNTO 0);
		PWM2:OUT STD_LOGIC_VECTOR(phases-1 DOWNTO 0);
		PWM3:OUT STD_LOGIC_VECTOR(phases-1 DOWNTO 0);
		ena:IN STD_LOGIC;
		duty:IN STD_LOGIC_VECTOR (resolution-1 DOWNTO 0));

END MAP1;

ARCHITECTURE PRO1 OF MAP1 IS
CONSTANT period: INTEGER :=CLOCK/PWM_CLOCK;
SIGNAL half_new : INTEGER RANGE 0 TO period/2:=0;
TYPE counter IS ARRAY (0 TO phases-1) OF INTEGER RANGE 0 TO period - 1;
SIGNAL count: counter:=(OTHERS=>0);
TYPE duties IS ARRAY (0 TO phases-1) OF INTEGER RANGE 0 TO period/2;
SIGNAL half: duties:= (OTHERS => 0);
BEGIN
PROCESS(CLKIN,reset)
BEGIN
	IF(reset='0')THEN
	PWM<=(OTHERS => '0');
	count<=(OTHERS=>0);
	ELSIF(CLKIN'EVENT AND CLKIN='1')THEN
	IF(ena='1')THEN
	half_new<=conv_integer(duty)*period/(2**resolution)/2;
	END IF;
	FOR i IN 0 TO phases-1 LOOP
	IF(count(0)=period - 1 - i*period/phases) THEN                      
          count(i) <= 0;                                                        
          half(i) <= half_new;        
	ELSE
	count(i)<=count(i)+1;
	END IF;
	END LOOP;
	FOR i IN 0 to phases-1 LOOP 
	IF(count(i)=half(i))THEN
	PWM(i)<='0';
	PWM2(i)<='0';
	PWM3(i)<='0';
	ELSIF(count(i) = period - half(i))THEN
	PWM(i)<='1';
	PWM2(i)<='1';
	PWM3(i)<='1';
	END IF;
	END LOOP;
	END IF;
	END PROCESS;

END PRO1;