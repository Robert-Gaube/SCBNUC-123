class Avion {
    private String planeID;
    private int totalEnginePower;

    public Avion(String planeID, int totalEnginePower) {
        this.planeID = planeID;
        this.totalEnginePower = totalEnginePower;
    }
    public String getPlaneID() {
        return this.planeID;
    }
    public int getTotalEnginePower() {
        return this.totalEnginePower;
    }
    protected void printPlaneID(String message) {
        System.out.println(this.planeID + message);
    }
    public void takeOff() {
        printPlaneID(" - Initiating takeof procedure - Starting engines - Accelerating down the runway - Taking of - Retracting gear - Takeof complete");
    }
    public void fly() {
        printPlaneID(" - Flying");
    }
    public void land() {
        printPlaneID(" - Initiating landing procedure - Enabling airbrakes - Lowering gear - Contacting runway - Decelerating - Stopping engines - Landing complete");
    }
}
class AvionCalatorii extends Avion {
    private int maxPassengers;

    public AvionCalatorii(String planeID, int totalEnginePower, int maxPassengers) {
        super(planeID, totalEnginePower);
        this.maxPassengers = maxPassengers;
    }
    public int getMaxPasengers() {
        return this.maxPassengers;
    }
}
class AvionBoeing extends AvionCalatorii {
    public AvionBoeing(String planeID, int totalEnginePower, int maxPassengers) {
        super(planeID, totalEnginePower, maxPassengers);
    }
}
class AvionConcorde extends AvionCalatorii {
    public AvionConcorde(String planeID, int totalEnginePower, int maxPassengers) {
        super(planeID, totalEnginePower, maxPassengers);
    }
    public void goSuperSonic() {
        printPlaneID(" - Supersonic mode activated");
    }
    public void goSubSonic() {
        printPlaneID(" - Supersonic mode deactivated");
    }
}
class AvionLupta extends Avion {
    public AvionLupta(String planeID, int totalEnginePower) {
        super(planeID, totalEnginePower);
    }
    public void launchMissile() {
        printPlaneID(" - Initiating missile launch procedure - Acquiring target - Launching missile - Breaking away - Missile launch complete");
    }
}
class AvionMig extends AvionLupta {
    public AvionMig(String planeID, int totalEnginePower) {
        super(planeID, totalEnginePower);
    }
    public void highSpeedGeometry() {
        printPlaneID(" - High speed geometry selected");
    }
    public void normalGeometry() {
        printPlaneID(" - Normal geometry selected");
    }
}
class AvionTomCat extends AvionLupta {
    public AvionTomCat(String planeID, int totalEnginePower) {
        super(planeID, totalEnginePower);
    }
    public void refuel() {
        printPlaneID(" - Initiating refueling procedure - Locating refueller - Catching up - Refueling - Refueling complete");
    }
}
class Main {
    public static void main(String[] argv) {
        AvionBoeing av1 = new AvionBoeing("JIIn1245", 100, 100);

        av1.takeOff(); av1.fly(); av1.land();

        AvionTomCat av2 = new AvionTomCat("awdubawyb", 100);

        av2.takeOff(); av2.fly(); av2.refuel(); av2.land();
    }
}