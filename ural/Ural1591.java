import java.io.*;
import java.util.*;
import java.math.*;

public class Ural1591 {

	static BigInteger choose(int n, int m) {
		BigInteger res = BigInteger.ONE;
		for (int i = 0; i < m; i++) {
			res = res.multiply(BigInteger.valueOf(n - i));
			res = res.divide(BigInteger.valueOf(i + 1));
		}
		return res;
	}

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int n = cin.nextInt();
		BigInteger ans = BigInteger.ZERO;
		if (n >= 4)
			ans = ans.add(choose(n, 4).multiply(BigInteger.valueOf(4)));
		if (n >= 5)
			ans = ans.add(choose(n, 5).multiply(BigInteger.valueOf(5)));
		if (n >= 6)
			ans = ans.add(choose(n, 6));
		System.out.println(ans);
	}
}
