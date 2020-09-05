with Ada.Text_IO; use Ada.Text_IO;

procedure main is

	G : Integer := 659;
	P : Integer := 929;
	Privkey1 : Integer := 397;
	PrivKey2 : Integer := 800;

	bit : array (0 .. 1) of Character := ('0', '1');

	function bin_image(N : Natural) return string is
		(if N < 2 then (1 => bit(n)) else bin_image(n/2) & bit (n mod 2));
	

	function ModularExponentiation(b : Integer; n : String; m : Natural) return Integer is
		X : Integer := 1;
		Power : Integer := b mod m;
	begin
		for i in reverse  0 .. n'length -1 loop
			if n(n'first + i) = '1' then
				X:= (X * Power) mod m;
			end if;
			power := (Power * Power) mod m;
		end loop;
		return X;
		
	end ModularExponentiation;

	protected type Person is
		procedure SetPrivKey(i : in Natural);
		function GetPublicKey return Integer;
		procedure CalcSharedPrivateKey(PubKey : in Integer);
		function GetPrivKey return Integer;
		function GetSharedPrivateKey return Integer;
	private
		PrivKey : Natural;
		SharedPrivKey : Integer;
	end Person;

	protected body Person is

		function GetPrivKey return Integer is
		begin
			return PrivKey;
		end GetPrivKey;

		procedure SetPrivKey(i : in Natural) is
		begin
			PrivKey := i;
		end SetPrivKey;

		function GetPublicKey return Integer is
		begin
			--return (G ** PrivKey) mod P;
			return ModularExponentiation(G, bin_image(PrivKey), P);
		end GetPublicKey;

		procedure CalcSharedPrivateKey(PubKey : in Integer) is
		begin
			--SharedPrivKey := (PubKey ** PrivKey) mod P;
			SharedPrivKey := ModularExponentiation(PubKey, bin_image(PrivKey), P);
		end CalcSharedPrivateKey;

		function GetSharedPrivateKey return Integer is
		begin
			return SharedPrivKey;
		end GetSharedPrivateKey;
	end Person;

	Alice : Person;
	Bob : Person;

begin
	Alice.SetPrivKey(PrivKey1);
	Bob.SetPrivKey(PrivKey2);



	Put_Line("Generator: " & Integer'Image(G));
	Put_Line("Primenumb: " & Integer'Image(P));

	Put_Line("Alice Priv: " & Integer'Image(Alice.GetPrivKey));
	Put_Line("Bob Priv: " & Integer'Image(Bob.GetPrivKey));

	Put_Line("Alice PUB: " & Integer'Image(Alice.GetPublicKey));
	Put_Line("Bob PUB: " & Integer'Image(Bob.GetPublicKey));

	Alice.CalcSharedPrivateKey(Bob.GetPublicKey);
	Bob.CalcSharedPrivateKey(Alice.GetPublicKey);

	Put_Line("Alice Shared Private Key is: " & Integer'Image(Alice.GetSharedPrivateKey));
	Put_Line("Bob   Shared Private Key is: " & Integer'Image(Bob.GetSharedPrivateKey));

end main;