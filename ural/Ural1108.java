import java.io.*;
import java.util.*;
import java.math.*;

public class Ural1108 {
	
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int n = cin.nextInt();
		if (n == 1) {
			System.out.println(2);
			return;
		}
		ArrayList<BigInteger> a = new ArrayList<BigInteger>();
		a.add(BigInteger.valueOf(2));
		a.add(BigInteger.valueOf(3));
		while (a.size() < n) {
			BigInteger last = a.get(a.size() - 1);
			a.add(last.subtract(BigInteger.ONE).multiply(last).add(BigInteger.ONE));
		}
		for (int i = 0; i < a.size(); i++)
			System.out.println(a.get(i));
	}
}

