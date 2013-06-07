package com.opdar.unqlite.exception;

public class UnqliteDatabaseException extends Exception{
	private static final long serialVersionUID = 4071899576932015466L;

	public static final int IO_ERR = -2;
	public static final int ITEM_NOT_FOUND = -6;
	public static final int CORRUPT = -24;
	public static final int READ_ONLY = -75;
	
	public UnqliteDatabaseException(int err) {
		super("err code : "+err+"  "+getErrorMessage(err));
		
	}
	
	private static String getErrorMessage(int err){
		switch (err) {
		case CORRUPT:
			return "�жϲ�����";
		case IO_ERR:
			return "���ݿ����δ�����������ȴ������ݿ�!";
		case ITEM_NOT_FOUND:
			return "δ�ҵ����ֶ����ݣ�";
		case READ_ONLY:
			return "��ǰ���ݿ⴦��ֻ��ģʽ��";
		default:
			return "";
		}
	}
	
}
