import java.io.*;
import java.util.*;
import java.math.*;

public class Ural1114 {

	static BigInteger[][][] c = new BigInteger[32][32][32];

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int n = cin.nextInt();
		int a = cin.nextInt();
		int b = cin.nextInt();
		for (int j = 0; j <= a; j++) {
			for (int k = 0; k <= b; k++)
				c[0][j][k] = BigInteger.ONE;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= a; j++) {
				for (int k = 0; k <= b; k++) {
					c[i][j][k] = BigInteger.ZERO;
					for (int j1 = 0; j1 <= j; j1++) {
						for (int k1 = 0; k1 <= k; k1++) {
							c[i][j][k] = c[i][j][k].add(c[i - 1][j1][k1]);
						}
					}
				}
			}
		}
		System.out.println(c[n][a][b]);
	}
}

