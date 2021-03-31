package core;

import static org.junit.Assert.*;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

/**
 * The test class LListTest.
 *
 * @author  Barry Brown
 * @version 9/19/2018 v1
 */
public class LListTest
{   
    @Test
    public void testCreateList()
    {
        LList<Integer> b = new LList<Integer>();
        assertEquals(0, b.size());
    }
    
    @Test
    public void testAddToList()
    {
        LList<String> b = new LList<String>();
        b.add("Hello");
        assertEquals(1, b.size());
        b.add("Bye");
        assertEquals(2, b.size());
        b.add("Adios");
        assertEquals(3, b.size());
    }
    
    @Test
    public void testAdd12()
    {
        LList<String> b = new LList<String>();
        b.add("str1");
        b.add("str2");
        b.add("str3");
        b.add("str4");
        b.add("str5");
        b.add("str6");
        b.add("str7");
        b.add("str8");
        b.add("str9");
        b.add("str10");
        b.add("str11");
        b.add("str12");
        assertEquals(12, b.size());
    }
    
    @Test
    public void testAdd100()
    {
        LList<String> b = new LList<String>();
    
        for (int i = 0; i < 50; i++)
            b.add("str" + i);
        assertEquals(50, b.size());
    
        for (int i = 0; i < 50; i++)
            b.add("morestr" + i);
        
        assertEquals(100, b.size());
    }

    @Test
    public void testAddFirst()
    {
        LList<String> a = new LList<String>();
        a.addFirst("str0");
        assertEquals("str0", a.get(0));
        a.addFirst("str1");
        assertEquals("str1", a.get(0));
        a.addFirst("str2");
        assertEquals("str2", a.get(0));
        assertEquals("str1", a.get(1));
        assertEquals("str0", a.get(2));
    }
   

    @Test
    public void testGet()
    {
        LList<String> b = new LList<String>();
        b.add("Hello");
        b.add("Bye");
        assertEquals("Hello", b.get(0));
        assertEquals("Bye", b.get(1));
    }
    
    @Test (expected=Party.class)
    public void testGetException()
    {
        LList<String> b = new LList<String>();
        b.add("Hello");
        b.get(1);
        // No more code after this, because the exception
        // will cause the method to exit.
        // Don't create more than one exception per test method.
    }
    
    @Test (expected=Party.class)
    public void testGetNegativeException()
    {
        LList b = new LList();
        b.get(-1);
    }
    
    @Test
    public void testGet12()
    {
        LList<String> b = new LList<String>();
        b.add("str1");
        b.add("str2");
        b.add("str3");
        b.add("str4");
        b.add("str5");
        b.add("str6");
        b.add("str7");
        b.add("str8");
        b.add("str9");
        b.add("str10");
        b.add("str11");
        b.add("str12");
        assertEquals("str8", b.get(7));
        assertEquals("str12", b.get(11));
        assertEquals("str1", b.get(0));
    }

    @Test
    public void testSet()
    {
        LList<String> b = new LList<String>();
        b.add("Hello");
        b.add("Bye");
        b.set(0, "Bonjour");
        assertEquals("Bonjour", b.get(0));
        assertEquals("Bye", b.get(1));
        b.set(1, "Adios");
        assertEquals("Bonjour", b.get(0));
        assertEquals("Adios", b.get(1));
    }
    
    @Test (expected=Party.class)
    public void testSetException()
    {
        LList<String> b = new LList<String>();
        b.add("Hello");
        b.set(1, "Bye");
        // No more code after this, because the exception
        // will cause the method to exit.
        // Don't create more that one exception per test method.
    }
    
    @Test (expected=Party.class)
    public void testSetEmptyException()
    {
        LList<String> b = new LList<String>();
        b.set(0, "Hello");
    }

    @Test (expected=Party.class)
    public void testSetNegativeException()
    {
        LList<String> b = new LList<String>();
        b.set(-1, "Hello");
    }

    @Test (expected=Party.class)
    public void testSetFullException()
    {
        LList<String> b = new LList<String>();
        b.add("Hello");
        b.add("Bye");
        b.set(2, "Bonjour");
    }
    
    @Test
    public void testToString()
    {
        LList<String> b = new LList<String>();
        assertEquals("[]", b.toString());
        b.add("hello");
        assertEquals("[hello]", b.toString());
        b.add("bye");
        assertEquals("[hello, bye]", b.toString());
        b.add("adios");
        assertEquals("[hello, bye, adios]", b.toString());
    }
    
    @Test
    public void testRemoveLast()
    {
        LList<String> b = new LList<String>();
        b.add("hello");
        b.add("hola");
        b.remove(1);
        assertEquals(1, b.size());
        assertEquals("hello", b.get(0));
        b.remove(0);
        assertEquals(0, b.size());
    }
	
    @Test
    public void testRemoveFirst()
    {
        LList<String> b = new LList<String>();
        b.add("hello");
        b.add("hola");
        b.remove(0);
        assertEquals(1, b.size());
        assertEquals("hola", b.get(0));
        b.remove(0);
        assertEquals(0, b.size());
    }
    
    @Test
    public void testRemoveLast10()
    {
        LList<String> b = new LList<String>();
        for (int i = 0; i < 10; i++)
            b.add("str" + i);
        assertEquals(10, b.size());
        b.remove(9);
        assertEquals(9, b.size());
        b.remove(8);
        b.remove(7);
        b.remove(6);
        b.remove(5);
        b.remove(4);
        b.remove(3);
        b.remove(2);
        b.remove(1);
        b.remove(0);
        assertEquals(0, b.size());
    }
    
    @Test (expected=Party.class)
    public void testRemove2Exception()
    {
        LList<String> b = new LList<String>();
        b.add("hello");
        b.remove(0);
        b.remove(0);
    }
   
    @Test
    public void testInsert()
    {
        LList<String> b = new LList<String>();
        b.add("hello");
        b.add("bye");
        b.insert(1, "adios");
        assertEquals("hello", b.get(0));
        assertEquals("adios", b.get(1));
        assertEquals("bye", b.get(2));
        assertEquals(3, b.size());
        
        b.insert(1, "buenos dias");
        assertEquals(4, b.size());
        assertEquals("hello", b.get(0));
        assertEquals("buenos dias", b.get(1));
        assertEquals("adios", b.get(2));
        
        b.insert(0, "hi");
        assertEquals(5, b.size());
        assertEquals("hi", b.get(0));
        assertEquals("hello", b.get(1));
        
        b.insert(4, "see ya");
        assertEquals(6, b.size());
        assertEquals("see ya", b.get(4));
        assertEquals("bye", b.get(5));
    }
    
    @Test
    public void testInsert11At0()
    {
        LList<String> b = new LList<String>();
        b.add("one");
        b.insert(0, "two");
        b.insert(0, "three");
        b.insert(0, "four");
        b.insert(0, "five");
        b.insert(0, "six");
        b.insert(0, "seven");
        b.insert(0, "eight");
        b.insert(0, "nine");
        b.insert(0, "ten");
        b.insert(0, "eleven");
        assertEquals(11, b.size());
        assertEquals("eleven", b.get(0));
        assertEquals("ten", b.get(1));
        assertEquals("two", b.get(9));
        assertEquals("one", b.get(10));
    }
    
    @Test (expected=Party.class)
    public void testInsertAt0Exception()
    {
        LList<String> b = new LList<String>();
        b.insert(0, "one");
    }
    
    @Test (expected=Party.class)
    public void testInsertException()
    {
        LList<String> b = new LList<String>();
        b.add("hello");
        b.insert(2, "bye");
    }
    
    @Test (expected=Party.class)
    public void testInsertNegative()
    {
        LList<String> b = new LList<String>();
        b.insert(-1, "hello");
    }


    @Test
    public void testRemove1()
    {
        LList<String> b = new LList<String>();
        b.add("hello");
        b.remove(0);
        assertEquals(0, b.size());
    }
    
    @Test
    public void testRemoveSeveral()
    {
        LList<String> b = new LList<String>();
        b.add("hello");
        b.add("bye");
        b.add("adios");
        b.add("ciao");
        b.add("see ya");
        b.remove(0);
        assertEquals(4, b.size());
        assertEquals("bye", b.get(0));
        assertEquals("adios", b.get(1));
        assertEquals("ciao", b.get(2));
        assertEquals("see ya", b.get(3));
        
        b.remove(3);
        assertEquals(3, b.size());
        assertEquals("bye", b.get(0));
        assertEquals("adios", b.get(1));
        assertEquals("ciao", b.get(2));
        
        b.remove(0);
        b.remove(0);
        b.remove(0);
        assertEquals(0, b.size());
    }
    
    @Test (expected=Party.class)
    public void testRemoveException()
    {
        LList<String> b = new LList<String>();
        b.add("hello");
        b.remove(1);
    }
    
    @Test (expected=Party.class)
    public void testRemoveNegative()
    {
        LList<String> b = new LList<String>();
        b.remove(-1);
    }
    
    @Test (expected=Party.class)
    public void testRemoveEmpty()
    {
        LList<String> b = new LList<String>();
        b.add("hello");
        b.remove(0);
        b.remove(0);
    }

    @Test
    public void testIndexOf()
    {
        LList<String> b = new LList<String>();
        
        for (int i = 0; i < 20; i++)
            b.add("str" + i);
        
        assertEquals(0, b.indexOf("str0"));
        assertEquals(19, b.indexOf("str19"));
        assertEquals(-1, b.indexOf("not found"));
    }
    
    @Test
    public void testIndexOfWithDuplicates()
    {
        LList<String> b = new LList<String>();
        b.add("str1");
        b.add("str2");
        b.add("str3");
        b.add("str2");
        b.add("str3");
        
        assertEquals(0, b.indexOf("str1"));
        assertEquals(1, b.indexOf("str2"));
        assertEquals(2, b.indexOf("str3"));
    }

    @Test
    public void testContains()
    {
        LList<String> b = new LList<String>();
        
        for (int i = 0; i < 20; i++)
            b.add("str" + i);
        
        assertTrue(b.contains("str0"));
        assertTrue(b.contains("str19"));
        assertFalse(b.contains("not found"));
    }

    
    // Make sure LList works with different kinds
    // of objects.
    
    @Test
    public void testInteger()
    {
        LList<Integer> b = new LList<Integer>();
        for (int i = 0; i < 50; i++)
            b.add(i);
        assertEquals(50, b.size());
        assertEquals(0, (int)b.get(0));
        assertEquals(1, (int)b.get(1));
        assertEquals(49, (int)b.get(49));
    }
    
    @Test
    public void testJFrame()
    {
        LList<javax.swing.JFrame> b = new LList<javax.swing.JFrame>();
        javax.swing.JFrame j1 = new javax.swing.JFrame();
        javax.swing.JFrame j2 = new javax.swing.JFrame();
        b.add(j2);
        b.add(j1);
        assertEquals(j2, b.get(0));
        assertEquals(j1, b.get(1));
    }
    
    
    @Test
    public void testRigorous1()
    {
        LList<String> a = new LList<String>();
        a.addLast("str0");
        a.addFirst("str1");
        a.addLast("str2");
        a.addFirst("str3");
        a.addLast("str4");
        assertEquals("str3", a.get(0));
        assertEquals("str1", a.get(1));
        assertEquals("str0", a.get(2));
        assertEquals("str2", a.get(3));
        assertEquals("str4", a.get(4));
        
        a.remove(0);
        assertEquals("str1", a.get(0));
        assertEquals("str0", a.get(1));
        assertEquals("str2", a.get(2));
        assertEquals("str4", a.get(3));
        
        a.remove(a.size()-1);
        assertEquals("str1", a.get(0));
        assertEquals("str0", a.get(1));
        assertEquals("str2", a.get(2));
        
        a.remove(0);
        assertEquals("str0", a.get(0));
        assertEquals("str2", a.get(1));
        
        a.remove(a.size()-1);
        assertEquals("str0", a.get(0));
        
        a.remove(a.size()-1);
        assertEquals(0, a.size());
    }

    @Test
    public void testRigorous2()
    {
        LList<Integer> a = new LList<Integer>();
        a.addLast(0);
        a.addFirst(1);
        a.insert(1, 2);
        a.insert(1, 3);
        a.insert(2, 4);
        a.remove(1);
        a.remove(0);
        a.insert(0, 5);
        a.remove(3);
        a.insert(2, 6);
        a.addLast(7);
        a.addFirst(8);
        a.remove(a.size()-1);
        a.remove(0);
        a.addFirst(9);
        a.remove(a.size()-1);
        a.set(3, 10);
        a.set(0, 11);
        // I hope I got this right! -BB
        assertEquals("[11, 5, 4, 10]", a.toString());
        a.remove(0);
        a.remove(0);
        assertEquals("[4, 10]", a.toString());
        a.remove(a.size()-1);
        assertEquals("[4]", a.toString());
    }
    
}