/*
 * cpp_util_2
 */

/*!
 * \file
 * \since v.2.4.0
 * \brief ������ ������ �� ��������� ������.
 */

#if !defined( CPP_UTIL_2__TEMPORARY_OBJECT_REF_HPP )
#define CPP_UTIL_2__TEMPORARY_OBJECT_REF_HPP

namespace cpp_util_2
{

//
// temporary_object_ref_t
//

/*!
 * \since v.2.4.0
 * \brief ������ ������ �� ��������� ������.
 *
 * ������ ����� �������� ��������������� ������������ ���
 * ����������� ���������� � C++98 �.�. rvalue references ��
 * �������� ��������� C++0x.
 *
 * <b>������ �������������.</b> �������� ���� ���������
 * ��������� ������������ �������� (��������, std::vector<int>).
 * ������ ����������� � ��������� �������� ����� ����������� �
 * ������� ����� ����� � ����������, ��� ���� ������������
 * ����� add, ���������� ����������� ������ �� std::vector<int>:
 * \code
 * class heavy_object_container_t
 * 	{
 * 	public:
 * 		void add( const std::vector<int> & obj ) {
 * 			m_underlying_storage.push_back( obj );
 * 		}
 * 	...
 * 	private:
 * 		std::list< std::vector<int> > m_underlying_storage;
 * 	};
 * \endcode
 * �� ������ ������� ��������, ��� ��� ���������� ������� �
 * ��������� ������������ ��������� ������, ������� �����
 * �������� ����� ����� ����������. � ���� ������ ��������
 * ���������� ����� ����������� ����� ���������� -- ������� ��
 * ��������� ������ add ��������� � ��� ��������:
 * \code
 * 		void add( std::vector<int> & obj ) {
 * 			m_underlying_storage.push_back( std::vector() );
 * 			m_underlying_storage.back().swap( obj );
 * 		}
 * \endcode
 * ��� ����� ������� ����������, ����� ��������� ������ add ���
 * ���������� ������� ���� ���������, ��� ��� ������� ������
 * ��������� ������.
 *
 * � C++0x ��� ���� ����� ����������� �� rvalue references, a
 * ��� C++98 ������������ ������ �����:
 * \code
 * 		void add( temporary_object_ref_t< std::vector<int> > obj ) {
 * 			m_underlying_storage.push_back( std::vector() );
 * 			m_underlying_storage.back().swap( obj.writeable() );
 * 		}
 * \endcode
 */
template< class T >
class temporary_object_ref_t
	{
	public :
		/*!
		 * ���������������� �����������.
		 *
		 * ������������ ������ �������������, ��� ����� �����
		 * ������� \a o ����� �������, ��� ����� ����� �������
		 * ���������� temporary_object_ref_t.
		 */
		explicit temporary_object_ref_t( T & o )
			:	m_object( o )
			{}

		/*!
		 * ��������� ������ ��������� ������ ��� ������������
		 * ��������� ���������� �������.
		 */
		T &
		writeable()
			{
				return m_object;
			}

		/*!
		 * ��������� ����������� ������ �� ��������� ������.
		 */
		const T &
		readonly() const
			{
				return m_object;
			}

	private :
		//! ������ �� ��������� ������.
		T & m_object;
	};

/*!
 * \since v.2.4.0
 * \brief ��������������� ������� ��� ��������� ������������
 * ������ �� ��������� ������.
 *
 * ������ �������������:
 * \code
 * void make_and_add_next_item(
 * 	heavy_object_container_t & container )
 * 	{
 * 		std::vector< int > next_item;
 * 		...
 * 		container.add( make_temporary_object_ref( next_item ) );
 * 	}
 * \endcode
 */
template< class T >
temporary_object_ref_t< T >
make_temporary_object_ref( T & o )
	{
		return temporary_object_ref_t< T >( o );
	}

} /* namespace cpp_util_2 */

#endif

