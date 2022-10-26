class Node {
    private int value;
    private Node next;

    public Node(int value) {
        this.value = value;
        this.next = null;
    }

    public void addNode(Node node) {
        System.out.println("First");
        Node tail = this;
        while(tail.next != null) {
            tail = tail.next;
        }
        tail.next = node;
    }

    public void addNode(Node node, int position) {
        System.out.println("Second");
        Node tail = this;
        int i = 0;
        while(tail.next != null && i < position - 1) {
            tail = tail.next;
            i++;
        }
        node.next = tail.next;
        tail.next = node;
        System.out.println(tail);
    }

    public String toString() {
        Node tail = this;
        String output = "";
        while(tail != null) {
            output += tail.value + " -> ";
            tail = tail.next;
        }
        output += "null";
        return output;
    }
}
class Main {
    public static void main(String[] argv) {
        Node list = new Node(5);
        list.addNode(new Node(10));
        list.addNode(new Node(12));
        list.addNode(new Node(60), 1);

        System.out.print(list);
    }
}