/*
 * cpp_util_2
 */

/*!
 * \file
 * \since v.2.4.0
 * \brief Шаблон ссылки на временный объект.
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
 * \brief Шаблон ссылки на временный объект.
 *
 * Данный класс является вспомогательным инструментом для
 * компенсации отсутствия в C++98 т.н. rvalue references из
 * будущего стандарта C++0x.
 *
 * <b>Пример использования.</b> Допустим есть некоторый
 * контейнер тяжеловесных объектов (например, std::vector<int>).
 * Иногда добавляемое в контейнер значение нужно скопировать и
 * создать новую копию в контейнере, для чего предназначен
 * метод add, получающий константную ссылку на std::vector<int>:
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
 * Но иногда заранее известно, что при добавлении объекта в
 * контейнер используется временный объект, который будет
 * выброшен сразу после добавления. В этом случае операцию
 * добавления можно реализовать более эффективно -- забрать из
 * аргумента метода add имеющееся в нем значение:
 * \code
 * 		void add( std::vector<int> & obj ) {
 * 			m_underlying_storage.push_back( std::vector() );
 * 			m_underlying_storage.back().swap( obj );
 * 		}
 * \endcode
 * При таком подходе желательно, чтобы сигнатура метода add для
 * временного объекта явно указывала, что она требует именно
 * временный объект.
 *
 * В C++0x для этих целей применялись бы rvalue references, a
 * для C++98 предназначен данный класс:
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
		 * Инициализирующий конструктор.
		 *
		 * Пользователь должен гарантировать, что время жизни
		 * объекта \a o будет большей, чем время жизни данного
		 * экземпляра temporary_object_ref_t.
		 */
		explicit temporary_object_ref_t( T & o )
			:	m_object( o )
			{}

		/*!
		 * Получение ссылки временный объект для последующего
		 * изменения временного объекта.
		 */
		T &
		writeable()
			{
				return m_object;
			}

		/*!
		 * Получение константной ссылки на временный объект.
		 */
		const T &
		readonly() const
			{
				return m_object;
			}

	private :
		//! Ссылка на временный объект.
		T & m_object;
	};

/*!
 * \since v.2.4.0
 * \brief Вспомогательная функция для упрощения формирования
 * ссылки на временный объект.
 *
 * Пример использования:
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

