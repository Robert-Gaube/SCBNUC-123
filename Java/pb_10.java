interface Salariu{
	public double calculSalar();
}

class Ore{
	private double hour;
	public Ore(double hour){
		this.hour=hour;
	}	
}
class Angajat{
	private String nume;
	public Angajat(String nume){
		this.nume=nume;
	}
}
abstract class Firma implements Salariu{
	protected Ore[] ora;
	protected int count=0;
	
	protected Angajat[] angajati;
	protected int nrAngajati=0;

	public  int addAngajat(Angajat p){
		for(int i=0;i<nrangajati;++i)
			if(p.nume.equals(angajati[i].nume))
				return -2;
		if(nrAngajati>1024)
			return -1;
		else{
			angajati[nrAngajati++]=p;
		}
	return 0;
	} 

	public double salariuMediu(){
		private double sumaSalarii=0;

		if(nrAngajati==0) return 0;

		for(int i=0;i<nrAngajati;++i){
			sumaSalarii+=angajati[i].afisareSalariu();
		}
		return sumaSalarii/nrAngajati;
	}

	abstract public void addOre(Ore h);
}

class AngajatCuSalarFix extends Firma{
	private double salariuFix;
	public AngajatCuSalariuFix(nume,salariuFix){
		super(nume);
		this.salariuFix=salariuFix;
	}
	public double calculSalar(){
		return salariuFix;
	}
	
	public void schimbaSalarFix(double altSalariu){
		this.salariufix=altSalariu;
	}

	public double afisareSalariu(){
		return this.salariuFix;
	}
}

class AngajatCuOra extends Firma{
	private double salariuPeOra;
	public AngajatCuOra (String nume , double salariuPeOra){
		super(nume);
		this.salariuPeOra=salariuPeOra;
	}
	
	public void addOre(Ore h){
		if(count>31){
			return;
		}
		else{
			ora[count++]=h;
		}
	}
	
	public void schimbaSalarPeOra(double altSalariu){
		this.salariuPeOra=altSalariu;
	}

	public double sumaOre(){
		private double suma=0;
		for(int i=0;i<count;++i){
			suma+=ora[i];
		}
	return suma;
	}
	public double afisareSalariu(){
		return this.salariuFix;
	}	
	public double calculSalar(){
		return (this.salariuPeOra*sumaOre());
	}

}

public main{
	public static void main(String[] args){
		Angajat angajat1=new AngajatCuSalarFix(new Angajat("andrei"),3000);
		Angajat angajat2=new AngajatCusalarFix(new Angajat("marius"),4800);
		Angajat angajat3=new AngajatCuOra(new Angajat("luca"),400);
		Angajat angajat4=new AngajatCuOra(new Angajat("faur"),299);
			
	
	}
}