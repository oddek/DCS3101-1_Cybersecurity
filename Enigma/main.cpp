#include <string>
#include <iostream>
#include <memory>
#include "Rotor.h"
#include "Enigma.h"

std::string formatString(std::string s)
{
	int num = 5;
	char sep = ' ';
	for(auto it = s.begin(); (num+1) <= std::distance(it, s.end()); it++)
	{
		std::advance(it, num);
		it = s.insert(it, sep);
	}
	return s;
}

int main()
{
	
	//auto rotor1 = new Rotor(alphabets[0]);
	int rotorIds[3] = {1,2,3};
	int reflektorId = 1;
	Enigma enigma(rotorIds, reflektorId);
	//Choose rotors 1-8 - Left to right;
	
	//Set offset 1-26 - Left to right;
	int offset[3] = {1,1,1};
	int ringSetting[3] = {1,1,1};

	enigma.setOffset(offset);
	enigma.setRingSetting(ringSetting);

	enigma.printRotorStatus();

	//std::string input = 		"DETTEERENFINTEKSTHVORMANKANTESTEENIGMAMASKINENSKIKKELIGDETERIKKEMULIGAAFINNEUTHVASOMSTAARHERNAARDETTEERBLITTKRYPTERTFORHAAPTENLIGVISSTEMMERDETMEDFASITOGDEKRYPTERINGDETTEERENFINTEKSTHVORMANKANTESTEENIGMAMASKINENSKIKKELIGDETERIKKEMULIGAAFINNEUTHVASOMSTAARHERNAARDETTEERBLITTKRYPTERTFORHAAPTENLIGVISSTEMMERDETMEDFASITOGDEKRYPTERINGDETTEERENFINTEKSTHVORMANKANTESTEENIGMAMASKINENSKIKKELIGDETERIKKEMULIGAAFINNEUTHVASOMSTAARHERNAARDETTEERBLITTKRYPTERTFORHAAPTENLIGVISSTEMMERDETMEDFASITOGDEKRYPTERINGDETTEERENFINTEKSTHVORMANKANTESTEENIGMAMASKINENSKIKKELIGDETERIKKEMULIGAAFINNEUTHVASOMSTAARHERNAARDETTEERBLITTKRYPTERTFORHAAPTENLIGVISSTEMMERDETMEDFASITOGDEKRYPTERINGDETTEERENFINTEKSTHVORMANKANTESTEENIGMAMASKINENSKIKKELIGDETERIKKEMULIGAAFINNEUTHVASOMSTAARHERNAARDETTEERBLITTKRYPTERTFORHAAPTENLIGVISSTEMMERDETMEDFASITOGDEKRYPTERING";
	std::string input = "DETTEERENFINTEKSTHVORMANKANTESTEENIGMAMASKINENSKIKKELIGDETERIKKEMULIGAAFINNEUTHVASOMSTAARHERNAARDETTEERBL";
	std::string encrypted = enigma.transform(input);
	
	enigma.setOffset(offset);
	//std::string decrypted = enigma.transform(encrypted);


	std::cout << "Input:     \n" << formatString(input) << "\n";
	//std::cout << "Alpha:     " << formatString("ABCDEFGHIJKLMNOPQRSTUVWXYZ") << "\n";

	std::cout << "Encrypted: \n" << formatString(encrypted) << "\n";

	//std::cout << "Decrypted: " << formatString(decrypted) << "\n";


	/*if(input.compare(decrypted) == 0)
	{
		std::cout << "Decrypt Success\n";
	}
	else
	{
		std::cout << "Decrypt Failure\n";
	}*/


	//std::string fasit = "mlhfr nnyvq bmnbq deqcj pzqqt xzgxi ayrqw hrnpn gbrhv awmgb qhuoo ccebt hhqsp jsqno ssqju hlmjm bptwp bcybg pnqwf gpayf dsljt wdimt gzfsd plzps ivnqt wqhds ojdfr uakmw yzkuy hgrfm ahnjx kdirr dqlku wpvbs vplzs fbsox hkbmp gvtig ccwoh hlpbc phgey ysabl bxmcs qircv wmtem rjtbc hekmd dgskf brlus hpwev fpajo bfgsi zsjcw acliq bffnm cswus pclgi wgaoh cextn uyrhy csurg ywsym cneul ignyd ickyb mlmes zndre bykbg ncuun qxvod fkzgu dnlmv matmt rvlnw fqzpx muztd dxbqj bumrj rxwlo hlgkx cosxr pttmf jxibe kyahf bkklu ypqxi haxom poher ygebj jagjm xfmzs npdoo ngltc vagnk axlbz rhmzi ysrlh oclwr acfms oghwd qwkfi dmkmz owcfv oixmr avbdf zjqfb hyvaa bxiiq biowj ktwrj uhhlj zzwxm djmey uzvsh eziaj hwync wesuz tzuwc wenmi zcdao blusd zihzq ijblf josar occdu rcssd iedzx hkdbe cekzy nsuna ljihz mptnx uybxr kafhi vuntn ncygf vwtad zdtde pcunx uzonk qxtjv hunrj wgfzi pycbv zehpv eywpe exclj doess wobus tzltr lfrsc xkawp xlxby gmgkp nzwit sewwj blbql qeize ufsfk gtyjs fptud ctkrg qkeql pvdvt";
	std::string fasit = "MLHFR NNYVQ BMNBQ DEQCJ PZQQT XZGXI AYRQW HRNPN GBRHV AWMGB QHUOO CCEBT HHQSP JSQNO SSQJU HLMJM BPTWP BCYBG PNQWF GPAYF DSLJT";
	std::transform(fasit.begin(), fasit.end(),fasit.begin(), ::toupper);
	std::cout << "Fasit: \n" << fasit << "\n";
	if(formatString(encrypted).compare(fasit) == 0)
	{
		std::cout << "Solution Success\n";
	}
	else
	{
		std::cout << "Solution Failure\n";
	}

}