with Ada.Text_IO; use Ada.Text_IO;

procedure main is

	function GCD(a : Integer; b : Integer) return Integer is
	a1 : Integer := Integer'max(a,b);
	b1 : Integer := Integer'min(a,b);
	begin
		if b = 0 then
			return a;
		else
			return GCD(b, a mod b);
		end if;
	end GCD;
begin
	Put_Line(Integer'Image(GCD(9, 27)));
	Put_Line(Integer'Image(GCD(1275, 2261)));
end main;
