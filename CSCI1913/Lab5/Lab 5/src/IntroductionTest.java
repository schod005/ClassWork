

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;


/**
 *
 * @author Jordan
 */
public class IntroductionTest {
    /**
     * Test of multiplyMatrix method, of class Introduction.
     */
    @Test
    public void testMultiplyMatrixNull() {
        System.out.println("multiplyMatrix");
        int[][] matrix = null;
        int multiplier = 0;
        Introduction instance = new Introduction();
        int[][] expResult = null;
        int[][] result = instance.multiplyMatrix(matrix, multiplier);
        assertArrayEquals("Test multiplyMatrix with a null matrix", expResult, result);
    }
    
    @Test
    public void testMultiplyMatrix() {
        int[][] matrix = {{1,2,3},{4,5,6},{7,8,9}};
        int multiplier = 2;
        Introduction instance = new Introduction();
        int[][] expResult = {{2,4,6},{8,10,12},{14,16,18}};
        int[][] result = instance.multiplyMatrix(matrix, multiplier);
        assertArrayEquals("Test multiplyMatrix with a non-null matrix", expResult, result);
    }

    /**
     * Test of rowSumProduct method, of class Introduction.
     */
    @Test
    public void testRowSumProductNullMatrix() {
        int[][] matrix = null;
        int currentRow = 0;
        Introduction instance = new Introduction();
        Integer expResult = null;
        Integer result = instance.rowSumProduct(matrix, currentRow);
        assertEquals("Test RowSumProduct with null matrix", expResult, result);
    }
    @Test
    public void testRowSumProduct() {
        int[][] matrix = {{1,2,3},{4,5,6},{7,8,9}};
        int currentRow = 0;
        Introduction instance = new Introduction();
        Integer expResult = 2160;
        Integer result = instance.rowSumProduct(matrix, currentRow);
        assertEquals("Test RowSumProduct with Non-null matrix", expResult, result);
    }
    
    @Test
    public void testRowSumProductPartial() {
        int[][] matrix = {{1,2,3},{4,5,6},{7,8,9}};
        int currentRow = 1;
        Introduction instance = new Introduction();
        Integer expResult = 360;
        Integer result = instance.rowSumProduct(matrix, currentRow);
        assertEquals("Test RowSumProduct with Non-null matrix", expResult, result);
    }
    @Test
    public void testRowSumProductInvalidRow() {
        int[][] matrix = {{1,2,3},{4,5,6},{7,8,9}};
        int currentRow = 4;
        Introduction instance = new Introduction();
        Integer expResult = null;
        Integer result = instance.rowSumProduct(matrix, currentRow);
        assertEquals("Test RowSumProduct with Non-null matrix", expResult, result);
    }
}
