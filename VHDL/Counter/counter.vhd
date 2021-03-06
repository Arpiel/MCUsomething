LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY DE115 IS
	PORT( CLKIN: IN STD_LOGIC;
			A7,B7,C7,D7,E7,F7:OUT STD_LOGIC_VECTOR (6 DOWNTO 0));

END DE115;

ARCHITECTURE TESTED OF DE115 IS

BEGIN
	PROCESS(CLKIN)
		VARIABLE TIMER : INTEGER RANGE 0 TO 50000000;
		VARIABLE ATIME,BTIME,CTIME,DTIME,ETIME,FTIME: INTEGER RANGE 0 TO 10;
		VARIABLE TCOUNT: INTEGER RANGE 0 TO 24;
	BEGIN
		IF(CLKIN'EVENT AND CLKIN='1')THEN
		TIMER:= TIMER+1;
		IF(TIMER=50000000) THEN 
			TIMER :=0;
			ATIME:=ATIME+1;
			IF(ATIME=10) THEN
			ATIME:=0;
			BTIME:=BTIME+1;
				IF(BTIME=6) THEN
				BTIME:=0;
				CTIME:=CTIME+1;
					IF(CTIME=10) THEN
					CTIME:=0;
					DTIME:=DTIME+1;
						IF(DTIME=6) THEN
						DTIME:=0;
						ETIME:=ETIME+1;
						TCOUNT:=TCOUNT+1;
							IF(ETIME=10) THEN
								ETIME:=0;
								FTIME:=FTIME+1;
									IF(TCOUNT=24) THEN
									FTIME:=0;
									ETIME:=0;
									TCOUNT:=0;
							END IF;
						END IF;
					END IF;
				END IF;
			 END IF;
			END IF;
		END IF;
	END IF;	
	CASE ATIME IS
		WHEN 0 => A7 <="1000000";
		WHEN 1 => A7 <="1111001";
		WHEN 2 => A7 <="0100100";
		WHEN 3 => A7 <="0110000";
		WHEN 4 => A7 <="0011001";
		WHEN 5 => A7 <="0010010";
		WHEN 6 => A7 <="0000010";
		WHEN 7 => A7 <="1011000";
		WHEN 8 => A7 <="0000000";
		WHEN 9 => A7 <="0011000";
		WHEN OTHERS => NULL;
	END CASE;
	CASE BTIME IS
		WHEN 0 => B7 <="1000000";
		WHEN 1 => B7 <="1111001";
		WHEN 2 => B7 <="0100100";
		WHEN 3 => B7 <="0110000";
		WHEN 4 => B7 <="0011001";
		WHEN 5 => B7 <="0010010";
		WHEN 6 => B7 <="0000010";
		WHEN 7 => B7 <="1011000";
		WHEN 8 => B7 <="0000000";
		WHEN 9 => B7 <="0011000";
		WHEN OTHERS => NULL;
	END CASE;
	CASE CTIME IS
		WHEN 0 => C7 <="1000000";
		WHEN 1 => C7 <="1111001";
		WHEN 2 => C7 <="0100100";
		WHEN 3 => C7 <="0110000";
		WHEN 4 => C7 <="0011001";
		WHEN 5 => C7 <="0010010";
		WHEN 6 => C7 <="0000010";
		WHEN 7 => C7 <="1011000";
		WHEN 8 => C7 <="0000000";
		WHEN 9 => C7 <="0011000";
		WHEN OTHERS => NULL;
	END CASE;
	CASE DTIME IS
		WHEN 0 => D7 <="1000000";
		WHEN 1 => D7 <="1111001";
		WHEN 2 => D7 <="0100100";
		WHEN 3 => D7 <="0110000";
		WHEN 4 => D7 <="0011001";
		WHEN 5 => D7 <="0010010";
		WHEN 6 => D7 <="0000010";
		WHEN 7 => D7 <="1011000";
		WHEN 8 => D7 <="0000000";
		WHEN 9 => D7 <="0011000";
		WHEN OTHERS => NULL;
	END CASE;
	CASE ETIME IS
		WHEN 0 => E7 <="1000000";
		WHEN 1 => E7 <="1111001";
		WHEN 2 => E7 <="0100100";
		WHEN 3 => E7 <="0110000";
		WHEN 4 => E7 <="0011001";
		WHEN 5 => E7 <="0010010";
		WHEN 6 => E7 <="0000010";
		WHEN 7 => E7 <="1011000";
		WHEN 8 => E7 <="0000000";
		WHEN 9 => E7 <="0011000";
		WHEN OTHERS => NULL;
	END CASE;
	CASE FTIME IS
		WHEN 0 => F7 <="1000000";
		WHEN 1 => F7 <="1111001";
		WHEN 2 => F7 <="0100100";
		WHEN 3 => F7 <="0110000";
		WHEN 4 => F7 <="0011001";
		WHEN 5 => F7 <="0010010";
		WHEN 6 => F7 <="0000010";
		WHEN 7 => F7 <="1011000";
		WHEN 8 => F7 <="0000000";
		WHEN 9 => F7 <="0011000";
		WHEN OTHERS => NULL;
	END CASE;
	END PROCESS;
END TESTED;