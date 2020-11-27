#include <iostream>
#include <string>

class egyszeru_sajat_hiba: public std::exception{

    const char* what() const noexcept override{
        return "Ez egy egyszeru sajat hiba!";
    }
};

class halozati_eroforras{
    unsigned hasznalt_portok=0;
public:
    halozati_eroforras(unsigned portok): hasznalt_portok(portok){}
    ~halozati_eroforras(){
        hasznalt_portok=0;
        std::cout<<"Portok felszabaditva"<<std::endl;
    }
    unsigned get_hasznalt_portok()const{
        return hasznalt_portok;
    }

};

class sajat_hiba: public std::exception{
    std::string message;
    int rossz_szam;
public:
    sajat_hiba(const std::string& message, int bad_number=0):message(message), rossz_szam(bad_number){}

    const char* what() const noexcept override{
        return message.c_str();
    }

    int get_bad_number()const{
        return rossz_szam;
    }

};

void hiba_kiiratas(const std::exception& e){
    std::cerr<<e.what()<<std::endl;
}

int oszt(int elso, int masodik){
    if(masodik<0){
        throw sajat_hiba("Nullaval valo osztas",masodik);
    }
    return elso/masodik;
}




int main() {


    egyszeru_sajat_hiba esh;
    hiba_kiiratas(esh);

    sajat_hiba sh("Ez a sajat hibam, keszen all a hasznalatra");
    hiba_kiiratas(sh);

    try{
        oszt(342,-34);
    }catch(sajat_hiba& exception){
        std::cerr<<exception.what()<<std::endl;
        std::cerr<<"A hibat az alabbi szam okozta: "<<exception.get_bad_number()<<std::endl;
    }



    /*try{
        int a= std::stoi("999999999999999999999999999999999999999999999999999999999999999999999999");

    }
    catch(const std::exception& error){
        std::cerr<<"A hiba konvertalas soran(exception tipussal): "<<error.what()<<std::endl;
    }
    catch(const std::out_of_range& error){
        std::cerr<<"A hiba konvertalas soran (masodik catch ag): "<<error.what()<<std::endl;

    }
    catch(const std::exception& error){
        std::cerr<<"Altalanos exception kezeles: "<<error.what()<<std::endl;
    }*/

    return 0;
}