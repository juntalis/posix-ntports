using System.ComponentModel;
using System.Linq;
using System.Reflection;

namespace Common
{

	public sealed class DefaultValueHelper
	{
		public static void InitializeDefaultValues<T>(T obj)
		{
			var properties = (
				obj.GetType()
					.GetProperties().Select(prop => new {
						prop,
						attr = GetDefaultValueAttribute(prop)
					}).Where(
						@t =>
						@t.attr !=
						null
					).Select(
						@t => new {
							Property = @t.prop,
							DefaultValue = @t.attr.Value
						}
					)
				).ToArray();
			foreach (var p in properties) {
				p.Property.SetValue(obj, p.DefaultValue, null);
			}
		}

		private static DefaultValueAttribute GetDefaultValueAttribute(PropertyInfo prop)
		{
			return prop.GetCustomAttributes(typeof(DefaultValueAttribute), true).Cast<DefaultValueAttribute>()
				.FirstOrDefault();
		}
	}


}